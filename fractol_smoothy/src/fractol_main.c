/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:18:06 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/19 04:10:55 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "time.h"

int	on_close(t_super *super)
{
	int	p_status;
	int	exit_status;

	printf("Attempting to close\n");
	printf("attempting to close MLX\n");
	mlx_close(super->mlx);
	exit_status = 0;
	if (super->pool && super->pool->pool_status == STATUS_RUNNING)
	{
		printf("attempting to close process pool\n");
		p_status = super->pool->pool_status;
		printf("p_status : %d\n", p_status);
		if (p_status == STATUS_CLOSED)
			printf("Process pool closed successfully.\n");
		else if (p_status == STATUS_BROKEN)
		{
			printf("process pool broken !\n");
			exit_status = 1;
		}
		else if (p_status == STATUS_RUNNING)
		{
			printf("pool running. Init regular closure procedure\n");
			close_process_pool(super->pool, NULL);
			usleep(100000);
			p_status = super->pool->pool_status;
			if (p_status == STATUS_BROKEN)
			{
				printf("pool still running after close attempt. Forcing closure\n");
				force_close_process_pool(super->pool, "pool still running after close. Forcing closure.");
				printf("Forced closure complet. exit status 2.\n");
				exit_status = 2;
			}
		}
	}
	printf("Fractol closure complet and successfull !\n");
	exit(exit_status);
}

void	frac_update(t_super *sup)
{
	t_shmem	*sm;
	t_img	*buff;

	sm = sup->shmem;
	printf("\n\n <<<<<< ----- ENTERING MULTIPROC UPDATE ----- >>>>>>>\n");
	printf("shared mem draw_buff before swap : %p\n", sm->draw_buff);
	if (sm->draw_buff == &sm->buff1)
		sm->draw_buff = &sm->buff2;
	else	
		sm->draw_buff = &sm->buff1;
	printf("shared mem draw_buff after swap : %p\n", sm->draw_buff);
	buff = sm->draw_buff;
	printf("Trying to clear buff %p\n", buff);
	printf("with addr %p\n", buff->addr);
	printf("and buff_size %zu\n", sup->mlx->buff_size);
	ft_memclear(buff->addr, sup->mlx->buff_size);
	printf("ordering pool draw !\n");
	if (order_pool_draw(sup->pool, sm) < 0)
	{
		on_close(sup);
		return ;
	}
	printf("pool draw successful !");
	ft_memcpy(sup->mlx->off_buff->addr, buff->addr, sup->mlx->buff_size);
	mlx_render_buffer(sup->mlx);
	printf(" <<<<<< ----- MULTIPROC UPDATE COMPLET ----- >>>>>>>\n\n\n");
}

void	give_mandelbrot_coord_rundown(t_pix *pix, t_frm *frm)
{
	frm->dist_func(pix);
//	mandelbrot_dist(pix, pix->z);
	printf("[ mandelbrot distance and value after %d iterations ]\n", pix->iters);
	printf("[ - value :	%f + %fi			]\n", creal(pix->z), cimag(pix->z));
	printf("[ - dist :	%f 				]\n", pix->dist);
}
/*
void	init_frame(t_frm *frm)
{
	frm->zoom = INIT_ZOOM;
	frm->px = INIT_POSX;
	frm->py = INIT_POSY;
	frm->cx = INIT_CREAL;
	frm->cy = INIT_CIMAG;
	frm->zoom = INIT_ZOOM;
	frm->ang = INIT_ANGLE;
	frm->dist_func = mandelbrot_dist;
}
*/

int	on_update(t_super *sup)
{
	static ssize_t	cumul_time;
	t_frm	*tfrm;
	t_frm	*sfrm;
	double	dfrm[6];

//	usleep(30000);
	cumul_time += ft_deltatime_usec();
//	printf("cumul_time : %zd, need update : %d\n", cumul_time, sup->needs_update);
	if ((!sup->needs_update) || (cumul_time < FRAME_USEC))
		return (0);
	tfrm = &sup->frm;
	sfrm = &sup->shmem->sfrm;
	dfrm[0] = tfrm->px - sfrm->px;
	dfrm[1] = tfrm->py - sfrm->py;
	dfrm[2] = tfrm->zoom - sfrm->zoom;
	dfrm[3] = tfrm->ang - sfrm->ang;
	dfrm[4] = tfrm->cx - sfrm->cx;
	dfrm[5] = tfrm->cy - sfrm->cy;
//	printf("normalized combined move : %f\n", (dfrm[0] + dfrm[1]) / sfrm->zoom );
//	printf("normalized zoom : %f\n", dfrm[2] / sfrm->zoom );
	printf("normalized rot : %f\n", dfrm[3]);
	if (((fabs(dfrm[0]) + fabs(dfrm[1])) / sfrm->zoom < MV_THLD)
		   	&& fabs(dfrm[2]) / sfrm->zoom < ZM_THLD && fabs(dfrm[3]) < RT_THLD
			&& (fabs(dfrm[4]) + fabs(dfrm[5])) < JL_THLD)
	{
		printf("HAHAHAHAHAHAHAH TARGET REACHED !");
		sup->needs_update = 0;
		return (0);
	}
	sfrm->px += dfrm[0] / SMOOTHNESS;
	sfrm->py += dfrm[1] / SMOOTHNESS;
	sfrm->zoom += dfrm[2] / SMOOTHNESS;
	sfrm->ang += dfrm[3] / SMOOTHNESS;
	sfrm->cx += dfrm[4] / SMOOTHNESS;
	sfrm->cy += dfrm[5] / SMOOTHNESS;
	frac_update(sup);
	cumul_time = 0;
	return (0);
}

static void	init_event_hooks(t_super *sup)
{
	init_mouse_data(sup);
	mlx_key_hook(sup->mlx->win, frac_key_switch, sup);
	mlx_hook(sup->mlx->win, ON_DESTROY, 0, on_close, sup);
	mlx_hook(sup->mlx->win, ON_MOUSEUP, (1L << 3), on_mouse_release, sup);
	mlx_hook(sup->mlx->win, ON_MOUSEDOWN, (1L << 2), on_mouse_press, sup);
	mlx_hook(sup->mlx->win, ON_MOUSEMOVE, (1L << 6), on_mouse_drag, sup);
}

int	main(int argc, char **argv)
{
	t_pool	pool;
	t_super	sup;
	t_frm	*frm;
	t_mlx	mlx;

	sup.shmem = mmap(NULL, sizeof(t_shmem) + sysconf(_SC_PAGE_SIZE) - (sizeof(t_shmem) % sysconf(_SC_PAGE_SIZE)), 
		PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (!sup.shmem)
		return (-1);
	printf("sizeof shared mem : %zu\n", sizeof(t_shmem) + (sizeof(t_shmem) % sysconf(_SC_PAGE_SIZE)));
	printf("raw sizeof shmem : %zu\n", sizeof(t_shmem));
	printf("aligning sizeof shmem : %zu, pagesize : %zu\n", sizeof(t_shmem) % sysconf(_SC_PAGE_SIZE), sysconf(_SC_PAGE_SIZE));
	printf("FRAME_USEC : %f\n", FRAME_USEC);

	init_frame(&sup.shmem->sfrm);
	if (!parse_inputs(sup.shmem->sfrm, argc, argv))
		return (1);
	frm = &sup.frm;
//	init_frame(frm);
//	init_base_color_palette(&frm->pal, PALETTE_MIAMI);
	*frm = sup.shmem->sfrm;

	if (init_process_pool(&pool, sup.shmem) < 0 || (pool.pool_status != STATUS_RUNNING))
	{
		close_process_pool(&pool, "Pool initialization failed");
		return (-1);
	}
	printf("pool initialized SUCCESSFULLY!\n");

	mlx_init_double_buff_window(&mlx, SCN_WIDTH, SCN_HEIGHT, "Fractol");
	printf("MLX started\n");
	printf("buff1.line_len : %d\n", mlx.buff1.line_len);
	printf("buff2.line_len : %d\n", mlx.buff2.line_len);
	printf("mlx.buffer_size : %zu\n", mlx.buff_size);
//	frac_print_defines();

	sup.mlx = &mlx;
	sup.pool = &pool;
	sup.shmem->buff1 = mlx.buff1;
	sup.shmem->buff2 = mlx.buff2;
	sup.shmem->buff1.addr = sup.shmem->buff1_data;
	sup.shmem->buff2.addr = sup.shmem->buff2_data;
	sup.needs_update = 1;

	printf("buff1 line_len, bytes per pixel: %d x %d\n", mlx.buff1.line_len, mlx.buff1.bytes_per_pxl);
	printf("buff_size before mouse_data : %zu\n", sup.mlx->buff_size);
	printf("buff_size before key_hook : %zu\n", sup.mlx->buff_size);

	init_event_hooks(&sup);
//	mlx_key_hook(mlx.win, frac_key_switch, &sup);
//	mlx_hook(mlx.win, ON_DESTROY, 0, on_close, &sup);
//	mlx_mouse_hook(mlx.win, on_mouse_wheel, &sup);//frac_mouse_click, &sup);
//	mlx_hook(mlx.win, ON_MOUSEUP, 0, on_mouse_release, &sup);
//	mlx_hook(mlx.win, ON_MOUSEDOWN, 0, on_mouse_press, &sup);
//	mlx_hook(mlx.win, ON_MOUSEMOVE, 0, on_mouse_drag, &sup);
//	mlx_loop_hook(mlx.conn, on_update, &sup);

	printf("mlx->buff_size before rendering : %zu\n", sup.mlx->buff_size);
//	mlx_set_bg_color(&mlx, 0x000000ff);
//	mlx_render_buffer(&mlx);
	frac_update(sup);
	mlx_loop(mlx.conn);
	return (0);
}
