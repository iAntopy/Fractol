/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event_switchs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:37:57 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/09 02:06:16 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	mouse_in_window(int x, int y)
{
	return ((y >= 0) && (x >= 0) && (y < SCN_HEIGHT) && (x < SCN_WIDTH));
}

void	init_mouse_data(t_super *sup)
{
	sup->mouse_1_pressed = 0;
	sup->mouse_3_pressed = 0;
	sup->mouse_1_dragging = 0;
	sup->mouse_3_dragging = 0;
}
/*
// In this section mouse click and mouse wheel events are seperate because
// click events trigger on release where wheel events trigger on roll (click).
int	on_mouse_wheel(int button, int x, int y, t_super *sup)
{
	printf("Mouse wheel rolled baby!\n");
	if (!mouse_in_window(x, y))
		return (0);
	if (button == 4)
//		frac_dir_zoom(sup, pix.fx, pix.fy, ZOOM_INCREMENT);
		frac_dir_zoom(sup, x, y, ZOOM_INCREMENT);
	else if (button == 5)
//		frac_dir_zoom(sup, pix.fx, pix.fy, -ZOOM_INCREMENT);
		frac_dir_zoom(sup, x, y, -ZOOM_INCREMENT);
	return (0);
}
*/
int	on_mouse_press(int button, int x, int y, t_super *sup)
{
	printf("Some mouse button pressed : %d\n", button);
	if (!mouse_in_window(x, y))
		return (0);
	else if (button == 1)
	{
		sup->mouse_1_pressed = 1;
		sup->last_x = x;
		sup->last_y = y;
	}
	else if (button == 3)
	{
		sup->mouse_3_pressed = 1;
		sup->last_x = x;
		sup->last_y = y;
	}
	else if (button == 4)
		frac_dir_zoom(sup, x, y, ZOOM_INCREMENT);
	else if (button == 5)
		frac_dir_zoom(sup, x, y, -ZOOM_INCREMENT);
	return (0);
}

// Moves frame to mouse position (left click) or get dist data at pix (right).
int	on_mouse_release(int button, int x, int y, t_super *sup)
{
	t_pix	pix;
	t_frm	*frm;

	if (!mouse_in_window(x, y))
		return (0);
//	else if (sup->mouse_1_pressed && !sup->mouse_1_dragging)//(sup->mouse_1_ || sup->mouse_3_pressed)
//	{
//		init_mouse_data(sup);
///		return (0);
//	}
	frm = sup->frm;
	printf("Pressed mouse button %d\n", button);
	printf("clicked at screen coord : (%d, %d)\n", x, y);
 	pix.sx = x;
	pix.sy = y;
	convert_pix_to_frame(frm, &pix, 1);
	printf("converted screen coords to : (%f, %f)\n", pix.fx, pix.fy);
	if (button == 1 && !sup->mouse_1_dragging)
		frac_set_frame_pos(sup, pix.fx, pix.fy);
	else if (button == 2)
		give_mandelbrot_coord_rundown(&pix, frm);
	init_mouse_data(sup);
	return (0);
}

int	on_mouse_drag(int x, int y, t_super *sup)
{
//	t_pix	pix;
//	t_frm	*frm;

	if (!mouse_in_window(x, y))
		return (0);
	else if (sup->mouse_1_pressed)
	{
		sup->mouse_1_dragging = 1;
		frac_move_frame(sup, sup->last_x - x, sup->last_y - y);
	}
	else if (sup->mouse_3_pressed)
	{
		sup->mouse_3_dragging = 1;
//		frm = sup->frm;
//		pix.sx = x;
//		pix.sy = y;
//		convert_pix_to_frame(frm, &pix, 0);
		frac_set_julia_shift(sup, (x - SCN_MIDX) * INIT_ZOOM, (y - SCN_MIDY) * INIT_ZOOM);
	}
	printf("mouse moved in window\n");
	sup->last_x = x;
	sup->last_y = y;
//	printf("Mouse is in window !\n");
	return (0);
}
