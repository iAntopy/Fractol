/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   celtic_dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:24:54 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/18 22:30:16 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
		sqx = fabs(sqx - sqy) + pix->fx;
		zy = 2 * zx * zy + pix->fy;
		zx = sqx;
		sqx = zx * zx;
		sqy = zy * zy;
	}
	pix->z = zx + zy * I;
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
		sqx = fabs(sqx - sqy) + pix->cx;
		zy = 2 * zx * zy + pix->cy;
		zx = sqx;
		sqx = zx * zx;
		sqy = zy * zy;
	}
	pix->z = zx + zy * I;
	pix->iters = i;
	pix->dist = sqx + sqy;
	return (pix);
}
