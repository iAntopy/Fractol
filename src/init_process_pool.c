/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process_pool.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:37:38 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/25 23:02:59 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <unistd.h>

static int	__proc_await_drawing_instruction(int idx, int pp[2], t_frm frm)
{
	int	img_stripe[DRAWN_AREA_NB_PIX];
	int	y_offset;

	y_offset = idx * DRAWN_Y_RANGE;
	printf("process %d setup to draw at y_offset %d\n", idx, y_offset);
	while (1)
	{
		read(pp[0], &frm, sizeof(t_frm));
		if (frm.instruction == SIG_STOP)
		{
			printf("process %d ordered to close\n", idx);
			close(pp[0]);
			close(pp[1]);
			break ;
		}
		else if (frm.instruction == SIG_DRAW)
		{
			printf("process %d order to draw\n", idx);
			draw_mandelbrot(img_stripe, &frm, y_offset, y_offset + DRAWN_Y_RANGE);
//			img_stripe[0] = 42;// DUMMY
			write(pp[1], img_stripe, sizeof(img_stripe));
		}
	}
	printf("process %d closed\n", idx);
	exit(0);
}

int	order_pool_draw(t_pool *pool, t_frm *frm, t_mlx *mlx)
{
	int	i;
//	int	drawn_stripe[DRAWN_AREA_NB_PIX];

	frm->instruction = SIG_DRAW;
	i = -1;
	while (++i < NB_DRAWING_PROCS)
		if (write(pool->wr_pipes[i], frm, sizeof(t_frm)) < 0)
			return (close_process_pool(pool, frm, "order_pool_draw : closing pool : write to pipe failed"));
	while (++i < NB_DRAWING_PROCS)
	{
//		printf("Pretend draw read from process index : %d\n", i);
		read(pool->rd_pipes[i], mlx->off_buff->addr + (i * DRAWN_AREA_NB_BYTES), DRAWN_AREA_NB_BYTES);
	}
	mlx_render_buffer(mlx);
	return (1);
}

int	frac_error(char *err_msg, int err_code)
{
	if (err_msg)
		fprintf(stderr, "%s\n", err_msg);
	return (err_code);
}

int	force_close_process_pool(t_pool *pool, char *err_msg)
{
	int	i;

	i = -1;
	while (++i < NB_DRAWING_PROCS)
	{
		if (pool->pids[i])
		{
			kill(pool->pids[i], SIGKILL);
			printf("Child proc %d with pid %d killed with msg : %s\n", i, pool->pids[i], err_msg);
		}
	}
	return (2);
}

int	close_process_pool(t_pool *pool, t_frm *frm, char *err_msg)
{
	int	i;

	i = -1;
	frm->instruction = SIG_STOP;
	while (++i < NB_DRAWING_PROCS)
		if (pool->wr_pipes[i] >= 0)
			write(pool->wr_pipes[i], frm, sizeof(t_frm));
	i = -1;
//	while (++i < NB_DRAWING_PROCS)
//		read(pool->rt_pipes[i], dump, DRAWN_AREA_NB_BYTES);

	while (++i < NB_DRAWING_PROCS)
	{
		if (pool->rd_pipes[i] >= 0)
			close(pool->rd_pipes[i]);
		if (pool->wr_pipes[i] >= 0)
			close(pool->wr_pipes[i]);
		pool->wr_pipes[i] = -1;
		pool->wr_pipes[i] = -1;
		pool->pids[i] = 0;
	}
	if (err_msg)
	{
		pool->pool_status = STATUS_BROKEN;
		return (frac_error(err_msg, -1));
	}
	pool->pool_status = STATUS_CLOSED;
	printf("all processes successfully closed !\n");
	return (0);
}

int	init_process_pool(t_pool *pool, t_frm *frm)
{
	int	i;
	int	fork_id;
	int	pp[2];
//	t_ppkg	pkg;

	ft_memclear(pool, sizeof(t_pool));
	i = -1;
	while (++i < NB_DRAWING_PROCS)
	{
		if (pipe(pp) < 0)
			return (close_process_pool(pool, frm, "closing pool : pipe failed"));
//		if (fcntl(pp[0], F_SETFL, O_NONBLOCKING) < 0)
//			return (close_proccess_pool(pool));
		pool->rd_pipes[i] = pp[0];
		pool->wr_pipes[i] = pp[1];
		fork_id = fork();
		if (fork_id == 0)
			__proc_await_drawing_instruction(i, pp, *frm);//Does not return
		else if (fork_id == -1)
			return (close_process_pool(pool, frm, "closing pool : forking failed"));
//		pool->status[i] = P_WAITING;
		pool->pids[i] = fork_id;
		printf("Parent spawn child with pid : %d\n", fork_id);
	}
	pool->pool_status = STATUS_RUNNING;
	return (1);
}
