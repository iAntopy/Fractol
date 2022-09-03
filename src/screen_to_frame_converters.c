/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_to_frame_converters.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 21:03:47 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/02 20:40:01 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_core.h"

void	convert_pix_to_frame(t_frm *frm, t_pix *pix)
{
	double	fx;
	double	fy;

	fx = pix->sx - frm->scn_midx;
	fy = pix->sy - frm->scn_midy;
	pix->fx = frm->zoom * (frm->cos_a * fx + frm->sin_a * fy) + frm->px;
	pix->fy = frm->zoom * (-frm->sin_a * fx + frm->cos_a * fy) + frm->py;
}

void	convert_vect_to_frame(t_frm *frm, t_pix *pix)
{
	double	fx;
	double	fy;

	fx = pix->sx;
	fy = pix->sy;
	pix->fx = frm->zoom * (frm->cos_a * fx + frm->sin_a * fy);
	pix->fy = frm->zoom * (-frm->sin_a * fx + frm->cos_a * fy);
}
