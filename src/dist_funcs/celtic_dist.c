/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   celtic_dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:24:54 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/27 06:06:27 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_core.h"

t_pix	*celtic_dist(t_pix *pix)
{
	int		i;
	double	zx;
	double	zy;
	double	sqx;
	double	sqy;

	zx = 0;
	zy = 0;
	sqx = 0;
	sqy = 0;
	i = -1;
	while (++i < MAX_ITER && (sqx + sqy) < BAILOUT_DIST)
	{
		sqy = fabs(sqy - sqx) + pix->fy;
		zx = 2 * zy * zx + pix->fx;
		zy = sqy;
		sqx = zx * zx;
		sqy = zy * zy;
	}
	pix->iters = i;
	pix->dist = sqx + sqy;
	return (pix);
}

t_pix	*celtic_julia_dist(t_pix *pix)
{
	int		i;
	double	zx;
	double	zy;
	double	sqx;
	double	sqy;

	zx = pix->fx;
	zy = pix->fy;
	sqx = zx * zx;
	sqy = zy * zy;
	i = -1;
	while (++i < MAX_ITER && (sqx + sqy) < BAILOUT_DIST)
	{
		sqy = fabs(sqy - sqx) + pix->cy;
		zx = 2 * zy * zx + pix->cx;
		zy = sqy;
		sqx = zx * zx;
		sqy = zy * zy;
	}
	pix->iters = i;
	pix->dist = sqx + sqy;
	return (pix);
}
