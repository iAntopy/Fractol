/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_switchs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:04:35 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/13 18:02:17 by iamongeo         ###   ########.fr       */
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
	else if (frm->dist_func == burning_ship_dist)
		frm->dist_func = burning_ship_julia_dist;
	else if (frm->dist_func == burning_ship_julia_dist)
		frm->dist_func = celtic_dist;
	else if (frm->dist_func == celtic_dist)
		frm->dist_func = celtic_julia_dist;
	else if (frm->dist_func == celtic_julia_dist)
		frm->dist_func = crown_dist;
	else if (frm->dist_func == crown_dist)
		frm->dist_func = crown_julia_dist;
	else if (frm->dist_func == crown_julia_dist)
		frm->dist_func = temple_dist;
	else if (frm->dist_func == temple_dist)
		frm->dist_func = temple_julia_dist;
	else if (frm->dist_func == temple_julia_dist)
		frm->dist_func = mandelbrot_5th_order_dist;
	else if (frm->dist_func == mandelbrot_5th_order_dist)
		frm->dist_func = julia_5th_order_dist;
	else
		frm->dist_func = mandelbrot_dist;
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

