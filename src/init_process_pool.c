/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process_pool.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:37:38 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/27 03:12:18 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <unistd.h>

static int	__proc_await_draw_order(int idx, int pp[4], t_frm frm)
{
	int	img_stripe[DRAWN_AREA_NB_PIX];
	int	y_offset;

	y_offset = idx * DRAWN_Y_RANGE;
	close_fd_ptr_list(2, pp, pp + 3);
	printf("process %d setup to draw at y_offset %d\n", idx, y_offset);
	while (1)
	{
		printf("process %d listening to orders. Good boy\n", idx);
		read(pp[2], &frm, sizeof(t_frm));
		if (frm.instruction == SIG_STOP)
		{
			printf("process %d ordered to close\n", idx);
			close_fd_ptr_list(2, pp + 1, pp + 2);
			break ;
		}
		else if (frm.instruction == SIG_DRAW)
		{
			printf("process %d ordered to draw\n", idx);
			draw_mandelbrot(img_stripe, &frm, y_offset, y_offset + DRAWN_Y_RANGE);
			printf("process %d draw order completed. Writing img data to pipe\n", idx);

//			img_stripe[0] = 42;// DUMMY
			write(pp[1], img_stripe, sizeof(img_stripe));
			printf("process %d successfully wrote to pipe\n", idx);
			printf("process %d wrap arround attempt\n", idx);
		}
		printf("process %d while over wraping around\n", idx);
	}
	printf("process %d closed\n", idx);
	exit(0);
}

int	order_pool_draw(t_pool *pool, t_frm *frm, t_mlx *mlx)
{
	int	i;
//	int	drawn_stripe[DRAWN_AREA_NB_PIX];

	printf("Main process ordering pool draw\n");
	frm->instruction = SIG_DRAW;
	i = -1;
	while (++i < NB_DRAWING_PROCS)
		if (write(pool->wr_pipes[i], frm, sizeof(t_frm)) < 0)
			return (close_process_pool(pool, frm, "order_pool_draw : closing pool : write to pipe failed"));
	i = -1;
	while (++i < NB_DRAWING_PROCS)
	{
//		printf("Pretend draw read from process index : %d\n", i);
		printf("Main process waiting for process %d results ...\n", i);
		read(pool->rd_pipes[i], mlx->off_buff->addr + (i * DRAWN_AREA_NB_BYTES), DRAWN_AREA_NB_BYTES + 1);
		printf("Main process received process %d results and wrote data to image buffer.\n", i);
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
	{
		if (pool->wr_pipes[i] >= 0)
		{
			printf("Sending close signal to process %d\n", i);
			write(pool->wr_pipes[i], frm, sizeof(t_frm));
		}
	}
	i = -1;
//	while (++i < NB_DRAWING_PROCS)
//		read(pool->rt_pipes[i], dump, DRAWN_AREA_NB_BYTES);

	while (++i < NB_DRAWING_PROCS)
	{
		printf("Closing process %d read pipe\n", i);
		if (pool->rd_pipes[i] >= 0)
			close(pool->rd_pipes[i]);
		printf("Closing process %d write pipe\n", i);
		if (pool->wr_pipes[i] >= 0)
			close(pool->wr_pipes[i]);
		printf("process %d pipe closed\n", i);
		pool->wr_pipes[i] = -1;
		pool->wr_pipes[i] = -1;
		pool->pids[i] = 0;
	}
	if (err_msg)
	{
		printf("closing pipe due to error\n");
		pool->pool_status = STATUS_BROKEN;
		return (frac_error(err_msg, -1));
	}
	pool->pool_status = STATUS_CLOSED;
	printf("all processes successfully closed with pool_status %d !\n", pool->pool_status);
	return (0);
}

int	init_process_pool(t_pool *pool, t_frm *frm)
{
	int	i;
	int	fork_id;
	int	pp[4];
//	t_ppkg	pkg;

	ft_memclear(pool, sizeof(t_pool));
	i = -1;
	while (++i < NB_DRAWING_PROCS)
	{
		if (pipe(pp) < 0 || pipe(pp + 2) < 0)
			return (close_process_pool(pool, frm, "closing pool : pipe failed"));
//		if (fcntl(pp[0], F_SETFL, O_NONBLOCKING) < 0)
//			return (close_proccess_pool(pool));
		fork_id = fork();
		if (fork_id == 0)
			__proc_await_draw_order(i, pp, *frm);//Does not return
		else if (fork_id < 0)
			return (close_process_pool(pool, frm, "closing pool : forking failed"));
		close_fd_ptr_list(2, pp + 1, pp + 2);

		pool->pids[i] = fork_id;
		pool->rd_pipes[i] = pp[0];
		pool->wr_pipes[i] = pp[3];
		printf("Parent spawn child with pid : %d\n", fork_id);
	}
	pool->pool_status = STATUS_RUNNING;
	return (1);
}
