/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 04:13:36 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/19 04:17:23 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	frac_zoom(t_super *sup, double increment)
{
	sup->frm.zoom *= 1 + increment;
	frac_update(sup);
	sup->needs_update = 1;
}

void	frac_dir_zoom(t_super *sup, double x, double y, double increment)
{
	double	cos_ang;
	double	sin_ang;
	double	sx;
	double	sy;
	double	ratio;

	ratio = sup->frm.zoom * increment * 1.1;
	cos_ang = cos(sup->shmem->sfrm.ang);
	sin_ang = sin(sup->shmem->sfrm.ang);
	sx = x - SCN_MIDX;
	sy = y - SCN_MIDY;
	sup->frm.px += (sx * cos_ang - sy * sin_ang) * ratio;
	sup->frm.py += (sx * sin_ang + sy * cos_ang) * ratio;
	sup->frm.zoom *= (1 - increment);
	sup->needs_update = 1;
}
