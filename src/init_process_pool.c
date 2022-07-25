/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process_pool.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:37:38 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/25 03:03:46 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <unistd.h>

//int	await_drawing_instruction()

int	close_process_pool(t_pool *pool)
{
	int	i;
	char	*sig;
	int	status;
	char	dump[4096];

	sig = NULL;
	i = -1;
	while (++i < NB_DRAWING_PROCS)
	{
		if (pool->status[i] == P_WAITING)
		{
			write(pool->wr_pipes[i], sig, sizeof(char *));
		//	waitpid(pool->pids[i], &status, 0);
		}
		else if (pool->status[i] == P_DONE)
			while (read(pool->rd_pipes[i], dump, 4096))
				continue ;
		else if (pool->status[i] == P_DRAWING)
			
		close(pool->rd_pipes[i]);
		close(pool->wr_pipes[i]);
		pool->wr_ppes[i] = 0;
		pool->rd_ppes[i] = 0;
		pool->status[i] = 0;


	}
	return (0);
}

int	init_process_pool(t_pool *pool)
{
	int	i;
	int	fork_id;
	t_ppkg	pkg;

	ft_memclear(pool, sizeof(t_pool));
	i = -1;
	while (++i < NB_DRAWING_PROCS)
	{
		if (pipe(pkg.pp) < 0)
			return (close_proccess_pool(pool));
		pkg.p_index = i;
		pool->rd_pipes[i] = pkg.pp[0];
		pool->wr_pipes[i] = pkg.pp[1];
		fork_id = fork();
		if (fork_id == 0)
			await_drawing_instruction(&pkg);//Does not return
		else if (fork_id == -1)
			return (close_process_pool(pool));
		pool->status[i] = P_WAITING;
		pool->pids[i] = fork_id;
	}
	return (1);
}
