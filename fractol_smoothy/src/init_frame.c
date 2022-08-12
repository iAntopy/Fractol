/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:28:14 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/11 15:30:18 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_frame(t_frm *frm)
{
	frm->zoom = INIT_ZOOM;
	frm->px = INIT_POSX;
	frm->py = INIT_POSY;
	frm->cx = INIT_CREAL;
	frm->cy = INIT_CIMAG;
	frm->zoom = INIT_ZOOM;
	frm->ang = INIT_ANGLE;
	frm->dist_func = mandelbrot_dist;
}

void	reset_frame(t_frm *frm)
{
	frm->zoom = INIT_ZOOM;
	frm->px = INIT_POSX;
	frm->py = INIT_POSY;
	frm->zoom = INIT_ZOOM;
	frm->ang = INIT_ANGLE;
	frm->dist_func = mandelbrot_dist;
}
