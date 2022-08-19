/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 23:23:33 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/18 23:23:45 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	frac_zoom(t_super *sup, double increment)
{
	sup->frm->zoom *= 1 + increment;
	frac_update(sup);
}

void	frac_dir_zoom(t_super *sup, double x, double y, double increment)
{
	t_frm	*frm;
	t_pix	pix;

	frm = sup->frm;
	pix.sx = x - SCN_MIDX;
	pix.sy = y - SCN_MIDY;
	convert_vect_to_frame(frm, &pix);
	frm->px += pix.fx * increment * 1.1;
	frm->py += pix.fy * increment * 1.1;
	sup->frm->zoom *= (1 - increment);
	frac_update(sup);
}
