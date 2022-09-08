/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:29:32 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/08 09:10:19 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	frac_move_frame(t_super *sup, double deltaX, double deltaY)
{
	t_pix	pix;

	pix.sx = deltaX;
	pix.sy = deltaY;
	convert_vect_to_frame(&sup->shmem->sfrm, &pix);
	sup->frm.px += pix.fx;
	sup->frm.py += pix.fy;
	sup->needs_update = 1;
}

void	frac_set_frame_pos(t_super *sup, double x, double y)
{
	sup->frm.px = x;
	sup->frm.py = y;
	sup->needs_update = 1;
}

void	frac_rotate(t_super *sup, double delta_ang)
{
	sup->frm.ang += delta_ang;
	sup->frm.cos_a = cos(sup->frm.ang);
	sup->frm.sin_a = sin(sup->frm.ang);
	sup->needs_update = 1;
}

void	frac_stop_animation(t_super *sup)
{
	sup->needs_update = 0;
	sup->frm = sup->shmem->sfrm;
}

void	frac_reset_frame(t_super *sup)
{
	reset_frame(&sup->frm);
	sup->needs_update = 1;
}
