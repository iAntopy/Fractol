/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_switchs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:04:35 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/07 16:16:16 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

static void	frac_admin_events_switch(int keycode, t_super *sup)
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

static void	frac_control_events_switch(int keycode, t_super *sup)
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
	frac_admin_events_switch(keycode, sup);
	frac_control_events_switch(keycode, sup);
	return (0);
}

