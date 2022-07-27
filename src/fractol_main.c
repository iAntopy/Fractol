/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:18:06 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/26 23:47:28 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "time.h"

void	frac_update(t_super *super)
{
	printf("Frac update :\n");
	printf("Super multiproc : %d\n", super->multiproc);
	if (super->multiproc)
	{
		printf("Multiproc update\n");
		frac_update_multiprocessor(super);
	}
	else
	{
		printf("Clearing buffer\n");
		printf("Clearing bufffffffffffffffffffffffffffffffffffffffffer\n");
		printf("super->mlx : %p\n", super->mlx);
		mlx_clear_buffer(super->mlx);
		printf("buffer cleared \n");
		draw_mandelbrot((int *)super->mlx->off_buff->addr, super->frm, 0, SCN_HEIGHT);
		mlx_render_buffer(super->mlx);
	}
	printf("Update DONE\n");
}

void	frac_update_multiprocessor(t_super *super)
{
	printf("\n\n <<<<<< ----- ENTERING MULTIPROC UPDATE ----- >>>>>>>\n");
	mlx_clear_buffer(super->mlx);
	printf("buffer cleared\n");
	order_pool_draw(super->pool, super->frm, super->mlx);
	mlx_render_buffer(super->mlx);
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

	frm = super->frm;
	printf("Pressed mouse button %d\n", button);
	printf("clicked at screen coord : (%d, %d)\n", x, y);
 	pix.sx = x;
	pix.sy = y;
	convert_pix_to_frame(frm, &pix, 1);
	printf("converted screen coords to : (%f, %f)\n", pix.fx, pix.fy);
	if (button == 1)
		frac_move_frame(super, (pix.fx - frm->px) / frm->zoom, (pix.fy - frm->py) / frm->zoom);
	else if (button == 3)
		give_mandelbrot_coord_rundown(&pix);
	return (0);
}

int	frac_key_switch(int keycode, t_super *super)
{
	printf("SOME KEY PRESSED : %d\n", keycode);
	if (keycode == KC_Enter)//36) 
		frac_update(super);
	else if (keycode == KC_Up)
		frac_move_frame(super, 0, -MOVE_INCREMENT);
	else if (keycode == KC_Down)
		frac_move_frame(super, 0, MOVE_INCREMENT);
	else if (keycode == KC_Left)
		frac_move_frame(super, -MOVE_INCREMENT, 0);
	else if (keycode == KC_Right)
		frac_move_frame(super, MOVE_INCREMENT, 0);
	else if (keycode == KC_PageUp)
		frac_zoom(super, -ZOOM_INCREMENT);
	else if (keycode == KC_PageDown)
		frac_zoom(super, ZOOM_INCREMENT);
	else if (keycode == KC_Home)
		frac_zoom(super, -(ZOOM_INCREMENT * 10));
	else if (keycode == KC_End)
		frac_zoom(super, ZOOM_INCREMENT * 10);
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
	printf("	FRM_WIDTH : %f\n	FRM_HEIGHT  %f\n	INIT_ZOOM : %f\n	INIT_POSX : %f\n	INIT_POSY : %f\n", FRM_WIDTH, FRM_HEIGHT, INIT_ZOOM, INIT_POSX, INIT_POSY);
	printf("	ASPECT_RATIO : %f\n", ASP_RATIO);
}

int	on_close(t_super *super)
{
	int	p_status;
	int	exit_status;

	printf("Attempting to close\n");
	printf("attempting to close MLX\n");
	mlx_close(super->mlx);
	printf("MLX closed successfully\n");
	exit_status = 0;
	if (super->pool)
	{
		printf("attempting to close process pool\n");
		p_status = super->pool->pool_status;
		printf("p_status : %d\n", p_status);
		close_process_pool(super->pool, super->frm, NULL);
		p_status = super->pool->pool_status;
		if (p_status == STATUS_CLOSED)
			printf("Process pool closed successfully.\n");
		else if (p_status == STATUS_BROKEN)
		{
			printf("process pool broken !\n");
			exit_status = 1;
		}
		else if (p_status == STATUS_RUNNING)
		{
			printf("pool still running. Forcing closure\n");
			usleep(500000);
			force_close_process_pool(super->pool, "pool still running at close. Forcing closure.");
			printf("Forced closure complet.\n");
			exit_status = 2;
		}
	}
	printf("Fractol closure complet and successfull !\n");
	exit(exit_status);
}

int	main(void)
{
	t_mlx	mlx;
	t_frm	frm;
	t_pool	pool;
	t_super	super_struct;

	frm.zoom = INIT_ZOOM;
	frm.px = INIT_POSX;
	frm.py = INIT_POSY;
	init_base_color_palette(&frm);
	
	if (MULTIPROC_RENDERING)
	{
		if (init_process_pool(&pool, &frm) < 0 || (pool.pool_status != STATUS_RUNNING))
		{
			close_process_pool(&pool, &frm, "Pool initialization failed");
			return (-1);
		}
	}
//	if (pool.pool_status == STATUS_RUNNING)
//		printf("Pool is active and ready to draw ...\n");
//	close_process_pool(&pool, &frm, NULL);
//	if (pool.pool_status == STATUS_CLOSED)
//	{
//		printf("Pool closed properly.\n");
//		return (0);
//	}
//	else if (pool.pool_status == STATUS_RUNNING)
//		printf("Pool close function called but is still running WOW !\n");
//	else if (pool.pool_status == STATUS_BROKEN)
//	{
//		printf("Process Pool Broken\n");
//		return (-1);
//	}

	mlx_init_double_buff_window(&mlx, SCN_WIDTH, SCN_HEIGHT, "Fractol");
	printf("MLX started\n");

	frac_print_defines();

	printf("mlx->off_buff : %p\n", mlx.off_buff);
	super_struct.mlx = &mlx;
	super_struct.frm = &frm;
	super_struct.multiproc = MULTIPROC_RENDERING;
	super_struct.pool = NULL;
	if (MULTIPROC_RENDERING)
		super_struct.pool = &pool;

	printf("buff1  line_len, bytes per pixel: %d x %d\n", mlx.buff1.line_len, mlx.buff1.bytes_per_pxl);

	mlx_key_hook(mlx.win, frac_key_switch, &super_struct);
	mlx_mouse_hook(mlx.win, frac_mouse_click, &super_struct);
	mlx_hook(mlx.win, ON_DESTROY, 0, on_close, &super_struct);
	
	mlx_set_bg_color(&mlx, 0x000000ff);
	mlx_render_buffer(&mlx);
//	order_pool_draw(&pool, &frm, &mlx);

	mlx_loop(mlx.conn);

	return (0);
}
