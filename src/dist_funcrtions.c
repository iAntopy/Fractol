/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_funcrtions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:52:39 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/13 18:07:08 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_pix	*mandelbrot_dist(t_pix *pix)
{
	int		i;
	double		zx;
	double		zy;
	double		sqx;
	double		sqy;

	zx = 0;
	zy = 0;
	sqx = 0;
	sqy = 0;
	i = -1;
	while (++i < MAX_ITER && (sqx + sqy) < BAILOUT_DIST)
	{
		sqx = zx * zx;
		sqy = zy * zy;
		zy = zx * zy;
		zy += zy - pix->fy;
		zx = sqx - sqy + pix->fx;
	}
	pix->z = zx + zy * I;
	pix->iters = i;
	pix->dist = sqx + sqy;
	return (pix);
}

t_pix	*julia_dist(t_pix *pix)
{
	int		i;
	double		zx;
	double		zy;
	double		sqx;
	double		sqy;

	zx = pix->fx;
	zy = pix->fy;
	sqx = zx * zx;
	sqy = zy * zy;
	i = -1;
	while (++i < MAX_ITER && (sqx + sqy) < BAILOUT_DIST)
	{
		zy = zx * zy;
		zy += zy - pix->cy;
		zx = sqx - sqy + pix->cx;
		sqx = zx * zx;
		sqy = zy * zy;
	}
	pix->z = zx + zy * I;
	pix->iters = i;
	pix->dist = sqx + sqy;
	return (pix);
}

t_pix	*burning_ship_dist(t_pix *pix)
{
	int			i;
	double		zx;
	double		zy;
	double		sqx;
	double		sqy;

	zx = 0;
	zy = 0;
	sqx = 0;
	sqy = 0;
	i = -1;
	while (++i < MAX_ITER && (sqx + sqy) < BAILOUT_DIST)
	{
		zy = fabs(zx * zy);
		zy += zy + pix->fy;
//		zy = 2 * abs(zx * zy) - pix->fy;
		zx = sqx - sqy - pix->fx;
		sqx = zx * zx;
		sqy = zy * zy;
	}
	pix->z = zx + zy * I;
	pix->iters = i;
	pix->dist = sqx + sqy;
	return (pix);
}

t_pix	*burning_ship_julia_dist(t_pix *pix)
{
	int			i;
	double		zx;
	double		zy;
	double		sqx;
	double		sqy;

	zx = pix->fx;
	zy = pix->fy;
	sqx = zx * zx;
	sqy = zy * zy;
	i = -1;
	while (++i < MAX_ITER && (sqx + sqy) < BAILOUT_DIST)
	{
		zy = fabs(zx * zy);
		zy += zy - pix->cy;
		zx = sqx - sqy + pix->cx;
		sqx = zx * zx;
		sqy = zy * zy;
	}
	pix->z = zx + zy * I;
	pix->iters = i;
	pix->dist = sqx + sqy;
	return (pix);
}

t_pix	*celtic_dist(t_pix *pix)
{
	int		i;
	double		zx;
	double		zy;
	double		sqx;
	double		sqy;

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
	double		zx;
	double		zy;
	double		sqx;
	double		sqy;

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
//		temp_zx = fabs(zx * zx - zy * zy) + pix->cx;
//		zy = 2 * zx * zy + pix->cy;
//		zx = temp_zx;
	}
	pix->z = zx + zy * I;
	pix->iters = i;
	pix->dist = sqx + sqy;
	return (pix);
}

t_pix	*temple_dist(t_pix *pix)
{
	int		i;
	double		zx;
	double		zy;
	double		sqx;
	double		sqy;

	zx = 0;
	zy = 0;
	sqx = 0;
	sqy = 0;
	i = -1;
	while (++i < MAX_ITER && (sqx + sqy) < BAILOUT_DIST)
	{
		sqx = fabs(zx * fabs(zx) - sqy) + pix->fx;
		zy = 2 * fabs(zx) * zy + pix->fy;
		zx = sqx;
		sqx = zx * zx;
		sqy = zy * zy;
	}
	pix->z = zx + zy * I;
	pix->iters = i;
	pix->dist = zx * zx + zy * zy;
	return (pix);
}

t_pix	*temple_julia_dist(t_pix *pix)
{
	int		i;
	double		zx;
	double		zy;
	double		sqx;
	double		sqy;

	zx = pix->fx;
	zy = pix->fy;
	sqx = zx * zx;
	sqy = zy * zy;
	i = -1;
	while (++i < MAX_ITER && (sqx + sqy) < BAILOUT_DIST)
	{
		sqx = fabs(zx * fabs(zx) - sqy) + pix->cx;
		zy = 2 * fabs(zx) * zy + pix->cy;
		zx = sqx;
		sqx = zx * zx;
		sqy = zy * zy;
//		temp_zx = fabs(zx * zx - zy * zy) + pix->cx;
//		zy = 2 * zx * zy + pix->cy;
//		zx = temp_zx;
	}
	pix->z = zx + zy * I;
	pix->iters = i;
	pix->dist = sqx + sqy;
	return (pix);
}

t_pix	*crown_dist(t_pix *pix)
{
	int	i;
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
		sqx = fabs(zx * fabs(zx) - sqy) -- pix->fx;
		zy = -2 * fabs(zx) * zy - pix->fy;
		zx = sqx;
		sqx = zx * zx;
		sqy = zy * zy;
	//	temp_zx = fabs(zx * fabs(zx) - zy * zy) + pix->fx;
	//	zy = -2 * fabs(zx) * zy + pix->fy;
	//	zx = temp_zx;
	}
	pix->z = zx + zy * I;
	pix->iters = i;
	pix->dist = sqx + sqy;
	return (pix);
}

t_pix	*crown_julia_dist(t_pix *pix)
{
	int	i;
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
		sqx = fabs(zx * fabs(zx) - sqy) - pix->cx;
		zy = -2 * fabs(zx) * zy - pix->cy;
		zx = sqx;
		sqx = zx * zx;
		sqy = zy * zy;
	}
	pix->z = zx + zy * I;
	pix->iters = i;
	pix->dist = sqx + sqy;
	return (pix);
}

t_pix	*mandelbrot_5th_order_dist(t_pix *pix)
{
	int		i;
	double		zx;
	double		zy;
	double		sq[5];

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
	pix->z = zx + zy * I;
	pix->iters = i;
	pix->dist = sq[0] + sq[1];
	return (pix);
}

t_pix	*julia_5th_order_dist(t_pix *pix)
{
	int		i;
	double		zx;
	double		zy;
	double		sq[5];

	zx = pix->fx;
	zy = pix->fy;
	sq[0] = zx * zx;
	sq[1] = zy * zy;
	i = -1;
	while (++i < MAX_ITER && (sq[0] + sq[1]) < BAILOUT_DIST)
	{
		sq[2] = sq[0] * sq[0];
		sq[3] = sq[1] * sq[1];
		sq[4] = sq[2] * sq[3];
		sq[5] = 10 * sq[4];
		zy = zy * (5 * sq[2] - sq[5] + sq[3]) + pix->cy;
		zx = zx * (sq[2] - sq[5] + 5 * sq[3]) + pix->cx;
		sq[0] = zx * zx;
		sq[1] = zy * zy;

	}
	pix->z = zx + zy * I;
	pix->iters = i;
	pix->dist = sq[0] + sq[1];
	return (pix);
}


