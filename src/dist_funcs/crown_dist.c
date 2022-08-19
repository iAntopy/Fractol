/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crown_dist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:26:03 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/18 22:30:51 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_pix	*crown_dist(t_pix *pix)
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
		sqy = fabs(zy * fabs(zy) - sqx) + pix->fy;
		zx = -2 * fabs(zy) * zx + pix->fx;
		zy = sqy;
		sqx = zx * zx;
		sqy = zy * zy;
	}
	pix->z = zx + zy * I;
	pix->iters = i;
	pix->dist = sqx + sqy;
	return (pix);
}

t_pix	*crown_julia_dist(t_pix *pix)
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
		sqy = fabs(zy * fabs(zy) - sqx) + pix->cy;
		zx = -2 * fabs(zy) * zx + pix->cx;
		zy = sqy;
		sqx = zx * zx;
		sqy = zy * zy;
	}
	pix->z = zx + zy * I;
	pix->iters = i;
	pix->dist = sqx + sqy;
	return (pix);
}
