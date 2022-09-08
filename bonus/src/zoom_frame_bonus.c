/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 04:13:36 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/08 09:10:26 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	frac_zoom(t_super *sup, double increment)
{
	sup->frm.zoom *= 1 + increment;
	sup->needs_update = 1;
}

void	frac_dir_zoom(t_super *sup, double x, double y, double increment)
{
	t_frm	*frm;
	t_pix	pix;

	frm = &sup->frm;
	pix.sx = x - frm->scn_midx;
	pix.sy = y - frm->scn_midy;
	convert_vect_to_frame(frm, &pix);
	frm->px += pix.fx * increment * 1.1;
	frm->py += pix.fy * increment * 1.1;
	frm->zoom *= (1 - increment);
	sup->needs_update = 1;
}
