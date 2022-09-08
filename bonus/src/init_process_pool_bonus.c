/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process_pool.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:37:38 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/08 09:09:41 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"
#include <unistd.h>
#include <sys/wait.h>

static int	__proc_await_draw_order(int idx, t_shmem *sm, char is_last)
{
	int			y_offset;
	int			drawn_range;
	int			sig;
	sigset_t	sigset;

	drawn_range = SCN_HEIGHT / NB_DRAWING_PROCS;
	y_offset = idx * drawn_range;
	drawn_range += is_last * (SCN_HEIGHT - (drawn_range * NB_DRAWING_PROCS));
	sigemptyset(&sigset);
	while (1)
	{
		sigaddset(&sigset, SIG_TERM);
		sigaddset(&sigset, SIG_DRAW);
		sigwait(&sigset, &sig);
		if (sig == SIG_TERM)
			break ;
		else if (sig == SIG_DRAW)
			draw_mandelbrot(sm->draw_buff, &sm->sfrm,
				y_offset, y_offset + drawn_range);
		sm->proc_draw_done[idx] = 1;
	}
	exit(0);
}

int	order_pool_draw(t_pool *pool, t_shmem *sm)
{
	int		i;
	ssize_t	dt;

	i = -1;
	while (++i < NB_DRAWING_PROCS)
	{
		sm->proc_draw_done[i] = 0;
		kill(pool->pids[i], SIG_DRAW);
	}
	dt = 0;
	i = -1;
	ft_deltatime_usec();
	while ((++i < NB_DRAWING_PROCS) && (dt < 1000000))
	{
		if (sm->proc_draw_done[i] == 0)
			i = -1;
		dt += ft_deltatime_usec();
	}
	if (dt >= 1000000)
		return (close_process_pool(pool,
				"Timeout waiting draw order completion."));
	return (1);
}

int	force_close_process_pool(t_pool *pool, char *err_msg)
{
	int	i;

	i = -1;
	while (++i < NB_DRAWING_PROCS)
		if (pool->pids[i])
			kill(pool->pids[i], SIGKILL);
	if (err_msg)
		fperror(err_msg);
	return (EXIT_FORCED_CLOSE);
}

int	close_process_pool(t_pool *pool, char *err_msg)
{
	int	i;

	i = -1;
	while ((++i < NB_DRAWING_PROCS) && (pool->pids[i] > 0))
	{
		kill(pool->pids[i], SIG_TERM);
		pool->pids[i] = 0;
	}
	wait(NULL);
	if (err_msg)
	{
		pool->pool_status = STATUS_BROKEN;
		fperror(err_msg);
		return (-1);
	}
	pool->pool_status = STATUS_CLOSED;
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
			__proc_await_draw_order(i, sm, (i == (NB_DRAWING_PROCS - 1)));
		else if (fork_id < 0)
			return (close_process_pool(pool,
					"closing pool : forking failed"));
		pool->pids[i] = fork_id;
	}
	pool->pool_status = STATUS_RUNNING;
	return (1);
}
