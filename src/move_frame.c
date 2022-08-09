/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:29:32 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/08 23:43:32 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	frac_move_frame(t_super *sup, double deltaX, double deltaY)
{
//	double	ratio;
//	double	cos_ang;
//	double	sin_ang;
//	double	Fx;
//	double	Fy;
//	double	ratio;
	t_pix	pix;

	pix.sx = deltaX;
	pix.sy = deltaY;
	convert_vect_to_frame(sup->frm, &pix);

//	convert_vect_to_frame(frm, &pix);
//	ratio = frm->zoom / INIT_ZOOM;
	
//	cos_ang = cos(sup->frm->ang);
//	sin_ang = sin(sup->frm->ang);
//	Fx = x - SCN_MIDX;
//	Fy = y - SCN_MIDY;
//	sup->frm->px += (deltaX * cos_ang + deltaY * sin_ang) * sup->frm->zoom;
//	sup->frm->py += (-deltaX * sin_ang + deltaY * cos_ang) * sup->frm->zoom;

//	frm->px += pix.fx;// * ratio;
//	frm->py += pix.fy;// * ratio;
	sup->frm->px += pix.fx;
	sup->frm->py += pix.fy;
	printf("new position : (%f, %f)\n", sup->frm->px, sup->frm->py);
	frac_update(sup);
}

void	frac_set_frame_pos(t_super *sup, double x, double y)
{
	sup->frm->px = x;
	sup->frm->py = y;
	frac_update(sup);
}

void	frac_zoom(t_super *sup, double increment)
{
	printf("Zooming by factor : %f\n", increment);
	sup->frm->zoom *= 1 + increment;
	frac_update(sup);
}

void	frac_rotate(t_super *sup, double delta_ang)
{
	printf("ATTEMPTING ROTATION !\n");
	sup->frm->ang += delta_ang;
	printf("NEW ANGLE AFTER ROTATION : %f\n", sup->frm->ang);
	frac_update(sup);
}

void	frac_dir_zoom(t_super *sup, double x, double y, double increment)
{
	t_frm	*frm;
	t_pix	pix;
//	double	cos_ang;
//	double	sin_ang;
//	double	Fx;
//	double	Fy;
//	double	ratio;

	frm = sup->frm;
	pix.sx = x - SCN_MIDX;
	pix.sy = y - SCN_MIDY;
	convert_vect_to_frame(frm, &pix);
	frm->px += pix.fx * increment * 1.1;
	frm->py += pix.fy * increment * 1.1;
	sup->frm->zoom *= (1 - increment);
//	ratio = sup->frm->zoom * increment * 1.1;
//	cos_ang = cos(sup->frm->ang);
//	sin_ang = sin(sup->frm->ang);
//	Fx = x - SCN_MIDX;
//	Fy = y - SCN_MIDY;
///	sup->frm->px += (Fx * cos_ang + Fy * sin_ang) * ratio;
//	sup->frm->py += (-Fx * sin_ang + Fy * cos_ang) * ratio;
	frac_update(sup);
}

void	frac_reset_frame(t_super *sup)
{
	sup->frm->px = INIT_POSX;
	sup->frm->py = INIT_POSY;
	sup->frm->zoom = INIT_ZOOM;
	sup->frm->ang = INIT_ANGLE;
	frac_update(sup);
}
