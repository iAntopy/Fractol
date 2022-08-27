/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifth_order_dist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:26:49 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/27 06:07:12 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_core.h"

t_pix	*mandelbrot_5th_order_dist(t_pix *pix)
{
	int		i;
	double	zx;
	double	zy;
	double	sq[5];

	zx = 0;
	zy = 0;
	sq[0] = 0;
	sq[1] = 0;
	i = -1;
	while (++i < MAX_ITER && (sq[0] + sq[1]) < BAILOUT_DIST)
	{
		sq[2] = sq[0] * sq[0];
		sq[3] = sq[1] * sq[1];
		sq[4] = sq[2] * (1 - 10 * sq[3]) + sq[3];
		zx = zx * (sq[4] + 4 * sq[3]) + pix->fx;
		zy = zy * (sq[4] + 4 * sq[2]) + pix->fy;
		sq[0] = zx * zx;
		sq[1] = zy * zy;
	}
	pix->iters = i;
	pix->dist = sq[0] + sq[1];
	return (pix);
}

t_pix	*julia_5th_order_dist(t_pix *pix)
{
	int		i;
	double	zx;
	double	zy;
	double	sq[5];

	zx = pix->fx;
	zy = pix->fy;
	sq[0] = zx * zx;
	sq[1] = zy * zy;
	i = -1;
	while (++i < MAX_ITER && (sq[0] + sq[1]) < BAILOUT_DIST)
	{
		sq[2] = sq[0] * sq[0];
		sq[3] = sq[1] * sq[1];
		sq[4] = sq[2] * (1 - 10 * sq[3]) + sq[3];
		zx = zx * (sq[4] + 4 * sq[3]) + pix->cx;
		zy = zy * (sq[4] + 4 * sq[2]) + pix->cy;
		sq[0] = zx * zx;
		sq[1] = zy * zy;
	}
	pix->iters = i;
	pix->dist = sq[0] + sq[1];
	return (pix);
}
