/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:29:32 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/15 20:59:18 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	frac_move_frame(t_super *sup, double deltaX, double deltaY)
{
//	double	ratio;
//	t_frm	*frm;
	t_pix	pix;

//	frm = sup->frm;
	pix.sx = deltaX;
	pix.sy = deltaY;
//	printf("init deltaXY : (%f, %f), vs original (%f, %f), zoom : %f\n", pix.sx, pix.sy, deltaX, deltaY, frm.zoom);

	convert_vect_to_frame(&sup->shmem->sfrm, &pix);
//	printf("converted deltaXY : (%f, %f)\n", pix.fx, pix.fy);
//	ratio = frm.zoom / INIT_ZOOM;
//	printf("frm.px, py : %lf, %lf\n", frm.px, frm.py);
//	printf("new position : %lf, %lf\n", frm.px + pix.fx, frm.py + pix.fy);
	sup->frm.px += pix.fx;// * ratio;
	sup->frm.py += pix.fy;// * ratio;
//	printf("deltaX, deltaY : %f, %f\n", deltaX, deltaY);
//	frm.px += deltaX * ratio;//sup->frm.zoom;
//	frm.py += deltaY * ratio;
	printf("new position : (%f, %f)\n", sup->frm.px, sup->frm.py);
//	frac_update(sup);
	sup->needs_update = 1;
	printf("moved frame : needs update : %d\n", sup->needs_update);
}

void	frac_set_frame_pos(t_super *sup, double x, double y)
{
	sup->frm.px = x;
	sup->frm.py = y;
	sup->needs_update = 1;
}

void	frac_zoom(t_super *sup, double increment)
{
	printf("Zooming by factor : %f\n", increment);
	sup->frm.zoom *= 1 + increment;
	frac_update(sup);
	sup->needs_update = 1;
}

void	frac_rotate(t_super *sup, double delta_ang)
{
	printf("ATTEMPTING ROTATION !\n");
	sup->frm.ang += delta_ang;
	printf("NEW ANGLE AFTER ROTATION : %f\n", sup->frm.ang);
	sup->needs_update = 1;
}

void	frac_dir_zoom(t_super *sup, double x, double y, double increment)
{
	double	cos_ang;
	double	sin_ang;
	double	Fx;
	double	Fy;
	double	ratio;

	ratio = sup->frm.zoom * increment * 1.1;
	cos_ang = cos(sup->shmem->sfrm.ang);
	sin_ang = sin(sup->shmem->sfrm.ang);
	Fx = x - SCN_MIDX;
	Fy = y - SCN_MIDY;
	sup->frm.px += (Fx * cos_ang - Fy * sin_ang) * ratio;
	sup->frm.py += (Fx * sin_ang + Fy * cos_ang) * ratio;
	sup->frm.zoom *= (1 - increment);
	sup->needs_update = 1;
}

void	frac_stop_animation(t_super *sup)
{
	sup->needs_update = 0;
	sup->frm = sup->shmem->sfrm;
}

void	frac_reset_frame(t_super *sup)
{
//	init_frame(&sup->frm);
	reset_frame(&sup->frm);
	sup->needs_update = 1;
}
