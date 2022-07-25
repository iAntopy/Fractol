/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:18:06 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/24 23:20:41 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "time.h"

void	frac_update(t_frm *frm)
{
	mlx_clear_buffer(frm->mlx);
	draw_mandelbrot(frm->mlx, frm);
	mlx_render_buffer(frm->mlx);
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
int	frac_mouse_click(int button, int x, int y, t_frm *frm)
{
	t_pix	pix;

	printf("Pressed mouse button %d\n", button);
	printf("clicked at screen coord : (%d, %d)\n", x, y);
 	pix.sx = x;
	pix.sy = y;
	convert_pix_to_frame(frm, &pix);
	printf("converted screen coords to : (%f, %f)\n", pix.fx, pix.fy);
	if (button == 1)
		frac_move_frame(frm, (pix.fx - frm->px) / frm->zoom, (pix.fy - frm->py) / frm->zoom);
	else if (button == 3)
		give_mandelbrot_coord_rundown(&pix);
	return (0);
}

int	frac_key_switch(int keycode, t_frm *frm)
{
	printf("SOME KEY PRESSED : %d\n", keycode);
	if (keycode == KC_Enter)//36) 
		frac_update(frm);
	else if (keycode == KC_Up)
		frac_move_frame(frm, 0, -MOVE_INCREMENT);
	else if (keycode == KC_Down)
		frac_move_frame(frm, 0, MOVE_INCREMENT);
	else if (keycode == KC_Left)
		frac_move_frame(frm, -MOVE_INCREMENT, 0);
	else if (keycode == KC_Right)
		frac_move_frame(frm, MOVE_INCREMENT, 0);
	else if (keycode == KC_PageUp)
		frac_zoom(frm, -ZOOM_INCREMENT);
	else if (keycode == KC_PageDown)
		frac_zoom(frm, ZOOM_INCREMENT);
	else if (keycode == KC_Home)
		frac_zoom(frm, -(ZOOM_INCREMENT * 10));
	else if (keycode == KC_End)
		frac_zoom(frm, ZOOM_INCREMENT * 10);

	
	return (0);
}

int	main(void)
{
	t_mlx	mlx;
	t_frm	frm;

	frm.zoom = INIT_ZOOM;
	frm.px = INIT_POSX;
	frm.py = INIT_POSY;
	
	printf("Pre init\n");
	mlx_init_double_buff_window(&mlx, SCN_WIDTH, SCN_HEIGHT, "Fractol");
	printf("Post init\n");

	init_base_color_palette(&frm);
	frm.mlx = &mlx;	
	frm.zoom = INIT_ZOOM;
	frm.px = INIT_POSX;
	frm.py = INIT_POSY;

	printf("buff1  line_len, bytes per pixel: %d x %d\n", mlx.buff1.line_len, mlx.buff1.bytes_per_pxl);

	mlx_key_hook(mlx.win, frac_key_switch, &frm);
	mlx_mouse_hook(mlx.win, frac_mouse_click, &frm);
	
	mlx_set_bg_color(&mlx, 0x000000ff);
	mlx_render_buffer(&mlx);

	mlx_loop(mlx.mlx);

	return (0);
}
