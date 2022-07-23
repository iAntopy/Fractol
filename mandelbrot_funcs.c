/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:27:04 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/23 00:07:42 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	convert_pix_to_frame(t_frm *frm, t_pix *pix)
{
//	printf("converting starts :\n");
//	printf("zoom %f, sx %i, sy %i\n", frm->zoom, pix->sx, pix->sy);
	pix->fx = frm->zoom * FRM_WIDTH * ((pix->sx - SCN_MIDX) / SCN_WIDTH) + frm->px;
	pix->fy = frm->zoom * FRM_HEIGHT * ((pix->sy - SCN_MIDY) / SCN_HEIGHT) + frm->py;
}

static void	draw_mandelbrot_pixel(t_img *buff, t_pix *pix, double dist)
{
	double	color_ratio;
	int		color;

	color_ratio = 100 / dist;
	color = 0xff0000 * color_ratio;		//RED
	color += 0xff00 * color_ratio;		//GREEN
	color += 0xff * color_ratio;		//BLUE
	
	printf("(sx, sy), (fx, fy), dist, col : (%d, %d), (%f, %f), %f, %d\n", pix->sx, pix->sy, pix->fx, pix->fy, dist, color);
	mlx_buff_put_pixel(buff, pix->sx, pix->sy, color);
}

// Returns dist after 100 iterations
static double	mandelbrot_dist(t_pix *pix)
{
	int				i;
	double complex	z;
	double complex	c;

//	printf("mandelbrot dist Starts \n");
	z = 0;
	c = pix->fx + (pix->fy * I);
	i = -1;
	while (++i < MAX_ITER)
	{
		z = (z * z) + c;
		if (fabs(creal(z)) > 1000)
			break ;
	}
	pix->z = z;
	return (hypot(creal(z), cimag(z)));
}

void	draw_mandelbrot(t_mlx *mlx, t_frm *frm)
{
	t_pix	pix;
	int		x;
	int		y;
	double	dist;

	y = -1;
	while (++y < SCN_HEIGHT)
	{
		x = -1;
		while (++x < SCN_WIDTH)
		{
			pix.sx = x;
			pix.sy = y;
			convert_pix_to_frame(frm, &pix);
			dist = mandelbrot_dist(&pix);

//			if ((45 < y && y < 55) && (45 < x && x < 55))
//			{
//				printf("drawing pix at (x, y) : (%d, %d),  dist : %f\n", x, y, dist);
//				printf("converted pix to frame : (%f, %f)\n", pix.fx, pix.fy);
//			}
			if (dist > 2)
			{
//				printf("WOW is < 2\n");
//				printf("drawing pix at (x, y) : (%d, %d),  dist : %f\n", x, y, dist);
//				printf("converted pix to frame : (%f, %f)\n", pix.fx, pix.fy);
				draw_mandelbrot_pixel(mlx->off_buff, &pix, dist);
			}
		}
	}
}
