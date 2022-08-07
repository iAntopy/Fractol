/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:18:06 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/07 16:18:01 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "time.h"

int	on_close(t_super *super)
{
	printf("Attempting to close\n");
	printf("attempting to close MLX\n");
	mlx_close(super->mlx);
	printf("MLX closed successfully\n");
	printf("Fractol closure complet and successfull !\n");
	exit(0);
}

void	frac_update(t_super *sup)
{
	printf("Frac update :\n");
	printf("Clearing buffer\n");
	printf("super->mlx : %p\n", sup->mlx);
	mlx_clear_buffer(sup->mlx);
	printf("buffer cleared \n");
	draw_mandelbrot(sup->mlx->off_buff, sup->frm);
	mlx_render_buffer(sup->mlx);
	printf("Update DONE\n");
}

/*
void	switch_julia_mandelbrot_mode(t_super *sup)
{
	t_frm	*frm;

	frm = sup->frm;
	if (frm->dist_func == mandelbrot_dist)
		frm->dist_func = julia_dist;
	else if (frm->dist_func == julia_dist)
		frm->dist_func = burning_ship_dist;
	else
		frm->dist_func = mandelbrot_dist;
	frm->cx = C_REAL;
	frm->cy = C_IMAG;
	frac_update(sup);
}

void	switch_color_palette(t_super *sup)
{
	t_frm	*frm;
	int	pal_code;

	frm = sup->frm;
	pal_code = frm->pal.pal_code;
	if (pal_code == PALETTE_MIAMI)
		init_base_color_palette(&frm->pal, PALETTE_MONOCHROME);
	else if (pal_code == PALETTE_MONOCHROME)
		init_base_color_palette(&frm->pal, PALETTE_ORANGE);
	else if (pal_code == PALETTE_ORANGE)
		init_base_color_palette(&frm->pal, PALETTE_GREEN);
	else if (pal_code == PALETTE_GREEN)
		init_base_color_palette(&frm->pal, PALETTE_MIAMI);
	printf("old pal_code vs new : %d, %d\n", pal_code, frm->pal.pal_code);
	printf("new nb cols : %d\n", frm->pal.nb_cols);
	frac_update(sup);
}
*/
void	give_mandelbrot_coord_rundown(t_pix *pix, t_frm *frm)
{
	frm->dist_func(pix);
//	mandelbrot_dist(pix, pix->z);
	printf("[ mandelbrot distance and value after %d iterations ]\n", pix->iters);
	printf("[ - value :	%f + %fi			]\n", creal(pix->z), cimag(pix->z));
	printf("[ - dist :	%f 				]\n", pix->dist);
}
/*
// Moves frame to mouse position
int	frac_mouse_click(int button, int x, int y, t_super *sup)//t_frm *frm)
{
	t_pix	pix;
	t_frm	*frm;

	if (y < 0 || x < 0)
		return (0);
	frm = sup->frm;
	printf("Pressed mouse button %d\n", button);
	printf("clicked at screen coord : (%d, %d)\n", x, y);
 	pix.sx = x;
	pix.sy = y;
	convert_pix_to_frame(frm, &pix, 1);
	printf("converted screen coords to : (%f, %f)\n", pix.fx, pix.fy);
	if (button == 1)
		frac_set_frame_pos(sup, pix.fx, pix.fy);
//		frac_move_frame(sup, (pix.fx - frm->px) / frm->zoom, (pix.fy - frm->py) / frm->zoom);
	else if (button == 3)
		give_mandelbrot_coord_rundown(&pix, frm);
	else if (button == 4)
		frac_dir_zoom(sup, pix.fx, pix.fy, -ZOOM_INCREMENT);
	else if (button == 5)
		frac_dir_zoom(sup, pix.fx, pix.fy, ZOOM_INCREMENT);
	return (0);
}

void	frac_admin_switch(int keycode, t_super *sup)
{	if (keycode == KC_Enter) 
		frac_update(sup);
	else if (keycode == KC_Escape)
		on_close(sup);
	else if (keycode == KC_Delete)
		frac_reset_frame(sup);
	else if (keycode == KC_Backspace)
		switch_julia_mandelbrot_mode(sup);
	else if (keycode == KC_c)
		switch_color_palette(sup);
}

void	frac_controls_switch(int keycode, t_super *sup)
{
	if ((keycode == KC_KP_8) || (keycode == KC_w))
		frac_move_frame(sup, 0, -MOVE_INCREMENT);
	else if ((keycode == KC_KP_5) || (keycode == KC_s))
		frac_move_frame(sup, 0, MOVE_INCREMENT);
	else if ((keycode == KC_KP_4) || (keycode == KC_a))
		frac_move_frame(sup, -MOVE_INCREMENT, 0);
	else if ((keycode == KC_KP_6) || (keycode == KC_d))
		frac_move_frame(sup, MOVE_INCREMENT, 0);
	else if ((keycode == KC_PageUp) || (keycode == KC_KP_Plus))
		frac_zoom(sup, -ZOOM_INCREMENT);
	else if ((keycode == KC_PageDown) || (keycode == KC_KP_Minus))
		frac_zoom(sup, ZOOM_INCREMENT);
	else if ((keycode == KC_KP_7) || (keycode == KC_q))
		frac_rotate(sup, ROT_INCREMENT);
	else if ((keycode == KC_KP_9) || (keycode == KC_e))
		frac_rotate(sup, -ROT_INCREMENT);
	else if (keycode == KC_Up)
		frac_shift_julia(sup, 0, JULIA_INCREMENT);
	else if (keycode == KC_Down)
		frac_shift_julia(sup, 0, -JULIA_INCREMENT);
	else if (keycode == KC_Left)
		frac_shift_julia(sup, -JULIA_INCREMENT, 0);
	else if (keycode == KC_Right)
		frac_shift_julia(sup, JULIA_INCREMENT, 0);
	else
		printf("\n\nKEY %d HAS NO BINDING !\n", keycode);
}

int	frac_key_switch(int keycode, t_super *sup)
{
	printf("SOME KEY PRESSED : %d\n", keycode);
	frac_admin_switch(keycode, sup);
	frac_controls_switch(keycode, sup);
	return (0);
}
*/
/*
	if (keycode == KC_Enter) 
		frac_update(sup);
	else if (keycode == KC_Escape)
		on_close(sup);
	else if (keycode == KC_Delete)
		frac_reset_frame(sup);
	else if (keycode == KC_Backspace)
		switch_julia_mandelbrot_mode(sup);
	else if (keycode == KC_c)
		switch_color_palette(sup);
	else if ((keycode == KC_KP_8) || (keycode == KC_w))
		frac_move_frame(sup, 0, -MOVE_INCREMENT);
	else if ((keycode == KC_KP_5) || (keycode == KC_s))
		frac_move_frame(sup, 0, MOVE_INCREMENT);
	else if ((keycode == KC_KP_4) || (keycode == KC_a))
		frac_move_frame(sup, -MOVE_INCREMENT, 0);
	else if ((keycode == KC_KP_6) || (keycode == KC_d))
		frac_move_frame(sup, MOVE_INCREMENT, 0);
	else if ((keycode == KC_PageUp) || (keycode == KC_KP_Plus))
		frac_zoom(sup, -ZOOM_INCREMENT);
	else if ((keycode == KC_PageDown) || (keycode == KC_KP_Minus))
		frac_zoom(sup, ZOOM_INCREMENT);
	else if ((keycode == KC_KP_7) || (keycode == KC_q))
		frac_rotate(sup, ROT_INCREMENT);
	else if ((keycode == KC_KP_9) || (keycode == KC_e))
		frac_rotate(sup, -ROT_INCREMENT);
	else if (keycode == KC_Up)
		frac_shift_julia(sup, 0, JULIA_INCREMENT);
	else if (keycode == KC_Down)
		frac_shift_julia(sup, 0, -JULIA_INCREMENT);
	else if (keycode == KC_Left)
		frac_shift_julia(sup, -JULIA_INCREMENT, 0);
	else if (keycode == KC_Right)
		frac_shift_julia(sup, JULIA_INCREMENT, 0);
	else
		printf("\n\nKEY %d HAS NO BINDING !\n", keycode);
	return (0);

}
*/
//DEBUG DELETE
void	frac_print_defines(void)
{
	printf("	SCN_WIDTH : %d\n	SCN_HEIGHT  %d\n	SCN_MIDX : %f\n	SCN_MIDY : %f\n", SCN_WIDTH, SCN_HEIGHT, SCN_MIDX, SCN_MIDY);
	printf("	INIT_ZOOM : %f\n	INIT_POSX : %f\n	INIT_POSY : %f\n", INIT_ZOOM, INIT_POSX, INIT_POSY);
	printf("	ASPECT_RATIO : %f\n", ASP_RATIO);
}

int	main(void)
{
	t_mlx	mlx;
	t_frm	frm;
	t_super	super_struct;

	frm.zoom = INIT_ZOOM;
	frm.px = INIT_POSX;
	frm.py = INIT_POSY;
	frm.ang = INIT_ANGLE;
	frm.cx = C_REAL;
	frm.cy = C_IMAG;
	frm.dist_func = mandelbrot_dist;
	init_base_color_palette(&frm.pal, PALETTE_MIAMI);
	
	mlx_init_double_buff_window(&mlx, SCN_WIDTH, SCN_HEIGHT, "Fractol");
	printf("MLX started\n");
	frac_print_defines();

	printf("mlx->screen_buff : %p\n", mlx.screen_buff);
	printf("mlx->off_buff : %p\n", mlx.off_buff);
	super_struct.mlx = &mlx;
	super_struct.frm = &frm;

	printf("buff1  line_len, bytes per pixel: %d x %d\n", mlx.buff1.line_len, mlx.buff1.bytes_per_pxl);

	mlx_key_hook(mlx.win, frac_key_switch, &super_struct);
	mlx_mouse_hook(mlx.win, frac_mouse_click, &super_struct);
	mlx_hook(mlx.win, ON_DESTROY, 0, on_close, &super_struct);
	
	mlx_set_bg_color(&mlx, 0x000000ff);
	mlx_render_buffer(&mlx);

	mlx_loop(mlx.conn);
	return (0);
}
