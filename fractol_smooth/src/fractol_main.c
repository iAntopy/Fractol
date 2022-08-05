/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:18:06 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/04 23:23:33 by iamongeo         ###   ########.fr       */
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
	if (sm->draw_buff == &sm->buff1)
		sm->draw_buff = &sm->buff2;
	else	
		sm->draw_buff = &sm->buff1;
	buff = sm->draw_buff;
	ft_memclear(buff->addr, sup->mlx->buff_size);
	if (order_pool_draw(sup->pool, sm) < 0)
	{
		on_close(sup);
		return ;
	}
	ft_memcpy(sup->mlx->off_buff->addr, buff->addr, sup->mlx->buff_size);
	mlx_render_buffer(sup->mlx);
	printf(" <<<<<< ----- MULTIPROC UPDATE COMPLET ----- >>>>>>>\n\n\n");
}

void	give_mandelbrot_coord_rundown(t_pix *pix)
{
	double	dist;
	int	iters;

	dist = mandelbrot_dist(pix, &iters);
	printf("[ mandelbrot distance and value after %d iterations ]\n", iters);
	printf("[ - value :	%f + %fi			]\n", creal(pix->z), cimag(pix->z));
	printf("[ - dist :	%f 				]\n", dist);
}

// Moves frame to mouse position
int	frac_mouse_click(int button, int x, int y, t_super *super)//t_frm *frm)
{
	t_pix	pix;
	t_frm	*frm;

	if (y < 0 || x < 0)
		return (0);
	frm = super->frm;
	printf("Pressed mouse button %d\n", button);
	printf("clicked at screen coord : (%d, %d)\n", x, y);
 	pix.sx = x;
	pix.sy = y;
	convert_pix_to_frame(frm, &pix, 1);
	printf("converted screen coords to : (%f, %f)\n", pix.fx, pix.fy);
	if (button == 1)
		frac_set_frame_pos(super, pix.fx, pix.fy);
	else if (button == 3)
		give_mandelbrot_coord_rundown(&pix);
	return (0);
}

int	frac_key_switch(int keycode, t_super *super)
{
	printf("SOME KEY PRESSED : %d\n", keycode);
	if (keycode == KC_Enter)//36) 
		frac_update(super);
	else if ((keycode == KC_Up) || (keycode == KC_KP_8))
		frac_move_frame(super, 0, -MOVE_INCREMENT);
	else if( (keycode == KC_Down) || (keycode == KC_KP_5))
		frac_move_frame(super, 0, MOVE_INCREMENT);
	else if ((keycode == KC_Left) || (keycode == KC_KP_4))
		frac_move_frame(super, -MOVE_INCREMENT, 0);
	else if ((keycode == KC_Right) || (keycode == KC_KP_6))
		frac_move_frame(super, MOVE_INCREMENT, 0);
	else if (keycode == KC_PageUp)
		frac_zoom(super, -ZOOM_INCREMENT);
	else if (keycode == KC_PageDown)
		frac_zoom(super, ZOOM_INCREMENT);
	else if ((keycode == KC_Home) || (keycode == KC_KP_Plus))
		frac_zoom(super, -(ZOOM_INCREMENT * 10));
	else if ((keycode == KC_End) || (keycode == KC_KP_Minus))
		frac_zoom(super, ZOOM_INCREMENT * 10);
	else if (keycode == KC_KP_7)
		frac_rotate(super, ROT_INCREMENT);
	else if (keycode == KC_KP_9)
		frac_rotate(super, -ROT_INCREMENT);
	else if (keycode == KC_Backspace)
		super->multiproc = !super->multiproc;
	else if (keycode == KC_P)
		frac_update_multiprocessor(super);
	return (0);
}

//DEBUG DELETE
void	frac_print_defines(void)
{
	printf("	SCN_WIDTH : %d\n	SCN_HEIGHT  %d\n	SCN_MIDX : %f\n	SCN_MIDY : %f\n", SCN_WIDTH, SCN_HEIGHT, SCN_MIDX, SCN_MIDY);
//	printf("	FRM_WIDTH : %f\n	FRM_HEIGHT  %f\n	INIT_ZOOM : %f\n	INIT_POSX : %f\n	INIT_POSY : %f\n", FRM_WIDTH, FRM_HEIGHT, INIT_ZOOM, INIT_POSX, INIT_POSY);
//	printf("	ASPECT_RATIO : %f\n", ASP_RATIO);
	printf("	BUFFER_SIZE : %zu\n", BUFFER_SIZE);
}

void	init_shared_frames(t_super *sup)
{
	t_shmem *sm;
	t_frm	*frm;

	sm = sup->shmem;
	frm = &sup->shmem->frm;
	frm->zoom = INIT_ZOOM;
	frm->px = INIT_POSX;
	frm->py = INIT_POSY;
	frm->palette = (int *)sup->shmem.palette;
	sup->shmem->cur_frm = *frm;
	init_base_color_palette(sup->shmem.palette);
}

int	main(void)
{
	t_mlx	mlx;
//	t_pool	pool;
	t_super	sup;
	t_frm	*frm;
	sigset_t	sigset;

	sup.shmem = mmap(NULL, sizeof(t_shmem) + sysconf(_SC_PAGE_SIZE) - (sizeof(t_shmem) % sysconf(_SC_PAGE_SIZE)), 
		PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (!sup.shmem)
		return (-1);
	printf("sizeof shared mem : %zu\n", sizeof(t_shmem) + (sizeof(t_shmem) % sysconf(_SC_PAGE_SIZE)));
	printf("raw sizeof shmem : %zu\n", sizeof(t_shmem));
	printf("aligning sizeof shmem : %zu, pagesize : %zu\n", sizeof(t_shmem) % sysconf(_SC_PAGE_SIZE), sysconf(_SC_PAGE_SIZE));
	
	init_shared_frames(&sup);
	sup->pman_pid = init_pool_manager(sup->shmem);
	sigemptyset(&sigset);

//	if (init_process_pool(&pool, sup.shmem) < 0 || (pool.pool_status != STATUS_RUNNING))
//	{
//		close_process_pool(&pool, "Pool initialization failed");
//		return (-1);
//	}

	mlx_init_double_buff_window(&mlx, SCN_WIDTH, SCN_HEIGHT, "Fractol");
	printf("MLX started\n");

	frac_print_defines();

	sup.mlx = &mlx;
	sup.frm = frm;
	sup.multiproc = MULTIPROC_RENDERING;
//	sup.pool = &pool;
	
	sup.shmem->buff1 = mlx.buff1;
	sup.shmem->buff2 = mlx.buff2;
	sup.shmem->buff1.addr = sup.shmem->buff1_data;
	sup.shmem->buff2.addr = sup.shmem->buff2_data;

	printf("buff1 line_len, bytes per pixel: %d x %d\n", mlx.buff1.line_len, mlx.buff1.bytes_per_pxl);

	mlx_key_hook(mlx.win, frac_key_switch, &sup);
	mlx_mouse_hook(mlx.win, frac_mouse_click, &sup);
	mlx_hook(mlx.win, ON_DESTROY, 0, on_close, &sup);

	mlx_set_bg_color(&mlx, 0x000000ff);
	mlx_render_buffer(&mlx);

	mlx_loop(mlx.conn);

	return (0);
}
