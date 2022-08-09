/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_to_frame_converters.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 21:03:47 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/08 23:35:01 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	convert_pix_to_frame(t_frm *frm, t_pix *pix)//, int print)
{
	double	cos_ang;
	double	sin_ang;
	double	fx;
	double	fy;

//	(void)print;
//	if (print)
//	{
//		printf("converting starts :\n");
///		printf("zoom %f, sx %i, sy %i\n", frm->zoom, pix->sx, pix->sy);
//	}

	cos_ang = cos(frm->ang);
	sin_ang = sin(frm->ang);
	fx = pix->sx - SCN_MIDX;
	fy = pix->sy - SCN_MIDY;
//	pix->fx = frm->zoom * (cos_ang * fx - sin_ang * fy) + frm->px;
//	pix->fy = frm->zoom * (sin_ang * fx + cos_ang * fy) + frm->py;
	pix->fx = frm->zoom * (cos_ang * fx + sin_ang * fy) + frm->px;
	pix->fy = frm->zoom * (-sin_ang * fx + cos_ang * fy) + frm->py;
//	if (print)
//		printf("converted coords : x %f, y %f\n", pix->fx, pix->fy);
}

void	convert_vect_to_frame(t_frm *frm, t_pix *pix)
{
	double	cos_ang;
	double	sin_ang;
	double	fx;
	double	fy;

	cos_ang = cos(frm->ang);
	sin_ang = sin(frm->ang);
	printf("cos_ang, sin_ang : %f, %f\n", cos_ang, sin_ang);
	fx = pix->sx;
	fy = pix->sy;
	printf("sx, sy : %f, %f\n", fx, fy);
//	pix->fx = frm->zoom * (cos_ang * fx - sin_ang * fy);
//	pix->fy = frm->zoom * (sin_ang * fx + cos_ang * fy);
	pix->fx = frm->zoom * (cos_ang * fx + sin_ang * fy);
	pix->fy = frm->zoom * (-sin_ang * fx + cos_ang * fy);
	printf("convert vect : fx, fy :  (%f, %f)\n", pix->fx, pix->fy);
}
