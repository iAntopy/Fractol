/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_to_frame_converters.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 21:03:47 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/19 04:18:11 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	convert_pix_to_frame(t_frm *frm, t_pix *pix)
{
	double	cos_ang;
	double	sin_ang;
	double	fx;
	double	fy;

	cos_ang = cos(frm->ang);
	sin_ang = sin(frm->ang);
	fx = pix->sx - SCN_MIDX;
	fy = pix->sy - SCN_MIDY;
	pix->fx = frm->zoom * (cos_ang * fx + sin_ang * fy) + frm->px;
	pix->fy = frm->zoom * (-sin_ang * fx + cos_ang * fy) + frm->py;
}

void	convert_vect_to_frame(t_frm *frm, t_pix *pix)
{
	double	cos_ang;
	double	sin_ang;
	double	fx;
	double	fy;

	cos_ang = cos(frm->ang);
	sin_ang = sin(frm->ang);
	fx = pix->sx;
	fy = pix->sy;
	pix->fx = frm->zoom * (cos_ang * fx + sin_ang * fy);
	pix->fy = frm->zoom * (-sin_ang * fx + cos_ang * fy);
}
