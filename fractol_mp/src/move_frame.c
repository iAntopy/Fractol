/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:29:32 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/07 15:54:50 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	frac_move_frame(t_super *sup, double deltaX, double deltaY)
{
	double	ratio;

	ratio = sup->frm->zoom / INIT_ZOOM;
	sup->frm->px += deltaX * ratio;//sup->frm->zoom;
	sup->frm->py += deltaY * ratio;//sup->frm->zoom;
//	if (sup->multiproc)
//		frac_update_multiprocessor(sup);
//	else
	frac_update(sup);
}

void	frac_set_frame_pos(t_super *sup, double x, double y)
{
	sup->frm->px = x;
	sup->frm->py = y;
//	if (sup->multiproc)
//		frac_update_multiprocessor(sup);
//	else
	frac_update(sup);
}

void	frac_zoom(t_super *sup, double increment)
{
	sup->frm->zoom *= 1 + increment;
//	if (sup->multiproc)
//		frac_update_multiprocessor(sup);
//	else
	frac_update(sup);
}

void	frac_rotate(t_super *sup, double delta_ang)
{
	printf("ATTEMPTING ROTATION !\n");
	sup->frm->ang += delta_ang;
	printf("NEW ANGLE AFTER ROTATION : %f\n", sup->frm->ang);
//	if (sup->multiproc)
//		frac_update_multiprocessor(sup);
//	else
	frac_update(sup);
}

void	frac_dir_zoom(t_super *sup, double x, double y, double increment)
{
	printf("Attempting directional zoom at (x, y) : (%f, %f) with factor : %f\n", x, y, increment);
	sup->frm->px = x;
	sup->frm->py = y;
	sup->frm->zoom *= 1 + increment;
	frac_update(sup);
}

void	frac_reset_frame(t_super *sup)
{
	sup->frm->px = 0;
	sup->frm->py = 0;
	sup->frm->zoom = INIT_ZOOM;
	sup->frm->ang = INIT_ANGLE;
	frac_update(sup);
}
