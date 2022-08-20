/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:18:06 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/20 07:29:14 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <time.h>

int	on_close(t_super *sup)
{
	int	p_status;

	printf("Initiating closure.\n");
	mlx_close(sup->mlx);
	p_status = sup->pool->pool_status;
	if (sup->pool && p_status == STATUS_RUNNING)
	{
		close_process_pool(sup->pool, NULL);
		usleep(100000);
		p_status = sup->pool->pool_status;
		if (p_status == STATUS_BROKEN)
			exit(force_close_process_pool(sup->pool,
					"Pool still running after close. Forcing closure."));
	}
	else if (p_status == STATUS_BROKEN)
		exit(force_close_process_pool(sup->pool,
				"Pool broken at close. Forcing closure."));
	ft_printf("Fractol closure complet and successfull !\n");
	exit(EXIT_SUCCESS);
}

static void	init_event_hooks_super_struct_and_shared_mem(t_super *sup)
{
	sup->shmem->buff1 = sup->mlx->buff1;
	sup->shmem->buff2 = sup->mlx->buff2;
	sup->shmem->buff1.addr = sup->shmem->buff1_data;
	sup->shmem->buff2.addr = sup->shmem->buff2_data;
	init_mouse_data(sup);
	mlx_key_hook(sup->mlx->win, frac_key_switch, sup);
	mlx_hook(sup->mlx->win, ON_DESTROY, 0, on_close, sup);
	mlx_hook(sup->mlx->win, ON_MOUSEUP, (1L << 3), on_mouse_release, sup);
	mlx_hook(sup->mlx->win, ON_MOUSEDOWN, (1L << 2), on_mouse_press, sup);
	mlx_hook(sup->mlx->win, ON_MOUSEMOVE, (1L << 6), on_mouse_drag, sup);
	mlx_loop_hook(sup->mlx->conn, on_update, sup);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_pool	pool;
	t_super	sup;
	size_t	pg_size;

	pg_size = sysconf(_SC_PAGE_SIZE);
	sup.shmem = mmap(NULL,
			sizeof(t_shmem) + pg_size - (sizeof(t_shmem) % pg_size),
			PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (!sup.shmem)
		return (EXIT_SHARED_MEM_FAILED);
	init_frame(&sup.shmem->sfrm);
	init_frame(&sup.frm);
	if (!parse_inputs(&sup.shmem->sfrm, argc, argv))
		return (EXIT_PARSING_FAILED);
	if (init_process_pool(&pool, sup.shmem) != 1)
		return (on_close(&sup));
	mlx_init_double_buff_window(&mlx, SCN_WIDTH, SCN_HEIGHT, "Fractol");
	sup.mlx = &mlx;
	sup.pool = &pool;
	init_event_hooks_super_struct_and_shared_mem(&sup);
	frac_update(&sup);
	mlx_loop(mlx.conn);
	return (EXIT_SUCCESS);
}
