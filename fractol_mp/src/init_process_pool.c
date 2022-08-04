/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process_pool.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:37:38 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/03 21:54:55 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

static int	__proc_await_draw_order(int idx, t_shmem *sm)
{
	int			y_offset;
	int			sig;
	sigset_t	sigset;

	sigemptyset(&sigset);
	y_offset = idx * DRAWN_Y_RANGE;
	
	while (1)
	{
		sigaddset(&sigset, SIG_STOP);
		sigaddset(&sigset, SIG_DRAW);
		sigwait(&sigset, &sig);
		printf("sig received from process %d : %d\n", idx, sig);
		if (sig == SIG_STOP)
		{
			printf("process %d received SIG_DRAW SIGNAL\n", idx);
			break ;
		}
		else if (sig == SIG_DRAW)
		{
			printf("process %d received SIG_DRAW signal\n", idx);
			draw_mandelbrot(sm->draw_buff, &sm->frm, y_offset, y_offset + DRAWN_Y_RANGE);
			printf("process %d draw mandelbrot DONE\n", idx);
		}
		sm->proc_draw_done[idx] = 1;
		printf("process %d draw status : %d\n", idx, sm->proc_draw_done[idx]);
	}
	exit(0);

/*
//	close_fd_ptr_list(2, pp, pp + 3);
	printf("process %d setup to draw at y_offset %d, with buffer size %zu\n", idx, y_offset, sizeof(img_stripe));
	while (1)
	{
		printf("process %d listening to orders. Good boy\n", idx);
		read(pp[2], &frm, sizeof(t_frm));
		if (frm.instruction == SIG_STOP)
		{
			printf("process %d ordered to close\n", idx);
			close(pp[1]);
			close(pp[2]);
//			close_fd_ptr_list(2, pp + 1, pp + 2);
			break ;
		}
		else if (frm.instruction == SIG_DRAW)
		{
			printf("process %d ordered to draw, last buff pix = %x\n", idx, img_stripe[DRAWN_AREA_NB_PIX - 1]);
			draw_mandelbrot(img_stripe, &frm, y_offset, y_offset + DRAWN_Y_RANGE);
			printf("process %d draw order completed. Writing img data to pipe last buff pix = %x\n", idx, img_stripe[DRAWN_AREA_NB_PIX - 1]);

//			img_stripe[0] = 42;// DUMMY
			write(pp[1], img_stripe, sizeof(img_stripe));
			printf("process %d successfully wrote to pipe\n", idx);
			printf("process %d wrap arround attempt\n", idx);
		}

		printf("process %d while over wraping around\n", idx);
	}
*/
	printf("process %d closed\n", idx);
	exit(0);
}

int	order_pool_draw(t_pool *pool, t_shmem *sm) 
{
	int	i;

	printf("Main process ordering pool draw\n");
	i = -1;
	while (++i < NB_DRAWING_PROCS)
	{
		printf("process %d draw order sending \n", i);
		sm->proc_draw_done[i] = 0;
		printf("process %d draw done set to false\n", i);
		kill(pool->pids[i], SIG_DRAW);
		printf("process %d draw order sent \n", i);
	}
	printf("All orders sent\n");
	printf("Parent process waiting for children .........\n");
	i = -1;
	while (++i < NB_DRAWING_PROCS)
		if (sm->proc_draw_done[i] == 0)
			i = -1;
	printf("Parent process waiting OVER!\n");

//	mlx_render_buffer(mlx);
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

int	close_process_pool(t_pool *pool, char *err_msg)
{
	int	i;

	i = -1;

/*
	frm->instruction = SIG_STOP;
	while (++i < NB_DRAWING_PROCS)
	{
		if (pool->wr_pipes[i] >= 0)
		{
			printf("Sending close signal to process %d\n", i);
			write(pool->wr_pipes[i], frm, sizeof(t_frm));
		}
	}
*/
	i = -1;
	while ((++i < NB_DRAWING_PROCS) && (pool->pids[i] > 0))
	{
		kill(pool->pids[i], SIG_STOP);
		pool->pids[i] = 0;
	}
	wait(NULL);
/*
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
*/
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

int	init_process_pool(t_pool *pool, t_shmem *sm)
{
	int		i;
	int		fork_id;

	ft_memclear(pool, sizeof(t_pool));
	i = -1;
	while (++i < NB_DRAWING_PROCS)
	{
		fork_id = fork();
		if (fork_id == 0)
			__proc_await_draw_order(i, sm);//ii, pp, *frm);//Does not return
		else if (fork_id < 0)
			return (close_process_pool(pool, "closing pool : forking failed"));

		pool->pids[i] = fork_id;
		printf("Parent spawn child with pid : %d\n", fork_id);
	}
	pool->pool_status = STATUS_RUNNING;
	return (1);
}
