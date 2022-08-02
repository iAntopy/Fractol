/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:27:04 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/28 00:30:45 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	convert_pix_to_frame(t_frm *frm, t_pix *pix, int print)
{
	if (print)
	{
		printf("converting starts :\n");
		printf("zoom %f, sx %i, sy %i\n", frm->zoom, pix->sx, pix->sy);
	}
	pix->fx = frm->zoom * FRM_WIDTH * ((pix->sx - SCN_MIDX) / SCN_WIDTH) + frm->px;
	pix->fy = frm->zoom * FRM_HEIGHT * ((pix->sy - SCN_MIDY) / SCN_HEIGHT) + frm->py;
	if (print)
		printf("converted coords : x %f, y %f\n", pix->fx, pix->fy);
}

static int	get_mandelbrot_pix_color(t_pix *pix, double dist, int iters, int print)
{
	int	*pcols[2];
	int	colors[3];
	int	color;
	double	interpolation;
	double	norm_iters;
//	double	ratio;
	int	i_iters;
//	double	red_ratio;
//	double	green_ratio;
//	double	blue_ratio;
	
//	ratio = 2 / (1 + exp(-0.01 * (1 / (dist - 2)))) + 1;
//	ratio = 2 / (1 + exp(-0.1 * (1 / (dist - 2)))) + 1;
	norm_iters = (NBCOLS - 1) * ((double)iters - log(log(dist) / 100)) / MAX_ITER;//log(BAILOUT_DIST));
//	ratio = norm_iters / MAX_ITER;
	i_iters = (int)norm_iters;
	interpolation = norm_iters - i_iters;
//	ratio = 1 / dist;
//	red_ratio = ratio;
//	green_ratio = ratio;
//	blue_ratio = ratio;
//	if (color_ratio > 1)
//		color_ratio = 1;
//	color = 0x00ffffff * ratio;
//	if (print)
//	{
//		printf("\niters %d, i_iters %d, norm_iters %f \n", iters, i_iters, norm_iters);
//		printf("dist %f, dist ratio %f\n", dist, dist_ratio);
//	}
	pcols[0] = pix->palette + (i_iters * 3);
	pcols[1] = pcols[0] + 3;
	colors[0] = (int)(pcols[0][0] + (pcols[1][0] - pcols[0][0]) * interpolation);
	colors[1] = (int)(pcols[0][1] + (pcols[1][1] - pcols[0][1]) * interpolation);
	colors[2] = (int)(pcols[0][2] + (pcols[1][2] - pcols[0][2]) * interpolation);
	color = (colors[0] << 16) | (colors[1] << 8) | colors[2];
	if (print)
	{
		printf("palette color 1 : r %d, g %d b %d\n", pcols[0][0], pcols[0][1], pcols[0][2]);
		printf("palette color 2 : r %d, g %d b %d\n\n", pcols[1][0], pcols[1][1], pcols[1][2]);
		printf("color : r %d g%d b %d\n", (color & 0xff0000) >> 16, (color & 0xff00) >> 8, color & 0xff);
	}
//	color += palette_cols[0][1] << 8;
//	color += palette_cols[0][2];

//	color = (int)(((palette_col & 0xff0000) >> 16) * dist_ratio) << 16;
//	color += (int)(((palette_col & 0xff00) >> 8) * dist_ratio) << 8;
//	color += (int)((palette_col & 0xff) * dist_ratio);

//	color = 0xff * red_ratio;
//	color <<= 8;
//	color += 0xff * green_ratio;
//	color <<= 8;
//	color += 0xff * blue_ratio;
//	color = ft_clamp(0xff * red_ratio, 0, 0xff);	//RED
//	color = (color * 0x100) + ft_clamp((0xff * green_ratio), 0, 0xff);
//	color = (color * 0x100) + ft_clamp((0xff * blue_ratio), 0, 0xff);
//	printf("(sx, sy), (fx, fy), dist, col : (%d, %d), (%f, %f), %f, %d\n", pix->sx, pix->sy, pix->fx, pix->fy, dist, color);


	return (color);
//	mlx_buff_put_pixel(buff, pix->sx, pix->sy, color);
//	mlx_buff_put_pixel(buff, pix->sx + 1, pix->sy, color);
//	mlx_buff_put_pixel(buff, pix->sx, pix->sy + 1, color);
//	mlx_buff_put_pixel(buff, pix->sx + 1, pix->sy + 1, color);
}

// Returns dist after 100 iterations
double	mandelbrot_dist(t_pix *pix, int *iters)
{
	int		i;
	double complex	z;
	double complex	c;
//	double		rl;
//	double		im;

//	printf("mandelbrot dist Starts \n");
	z = -1;
	c = pix->fx + (pix->fy * I);
	i = -1;
	while (++i < MAX_ITER && hypot(creal(z), cimag(z)) < BAILOUT_DIST)
	{
		z = (z * z) + c;
//		if (fabs(creal(z)) > 1000)//2 || fabs(cimag(z)) > 2)
//			break ;
	}
	pix->z = z;
	*iters = i;
	return (hypot(creal(z), cimag(z)));
}

//void	draw_mandelbrot(t_mlx *mlx, t_frm *frm, int y_range[2], void (*draw_func)())
void	draw_mandelbrot(int *arr, t_frm *frm, int y_start, int y_end)
{
	t_pix	pix;
	int		x;
	int		y;
	double	dist;
	int	iters;
	int		color;
	
	printf("pid %d draw_mandelbrot starts\n", getpid());
//	pix.palette = (int *)frm->palette;
//	printf("Corner color in frame : r %d g %d b %d \n", frm->palette[0][0], frm->palette[0][1], frm->palette[0][2]);
	
	y = y_start - 1;
	while (++y < y_end)
	{
		x = -1;
		while (++x < SCN_WIDTH)
		{
			pix.sx = x;
			pix.sy = y;
			convert_pix_to_frame(frm, &pix, (!y && !x));
			dist = mandelbrot_dist(&pix, &iters);

//			if ((45 < y && y < 55) && (45 < x && x < 55))
//			{
//				printf("drawing pix at (x, y) : (%d, %d),  dist : %f\n", x, y, dist);
//				printf("converted pix to frame : (%f, %f)\n", pix.fx, pix.fy);
//			}
//			if (dist > 2)
//			{
//				printf("WOW is < 2\n");
//				printf("drawing pix at (x, y) : (%d, %d),  dist : %f\n", x, y, dist);
//				printf("converted pix to frame : (%f, %f)\n", pix.fx, pix.fy);
//			}
			if (iters < MAX_ITER)
			{
				pix.palette = (int *)frm->palette;
				color = get_mandelbrot_pix_color(&pix, dist, iters, (!y && !x));
//				mlx_buff_put_pixel(mlx_off_buff, x, y, color);
//				mlx_buff_put_pixel(buff, x + 1, y, color);
//				mlx_buff_put_pixel(buff, x, y + 1, color);
//				mlx_buff_put_pixel(buff, x + 1, y + 1, color);
				arr[(y - y_start) * SCN_WIDTH + x] = color;
			}
//			x += 2;
		}
//		y += 2;
	}
	printf("pid %d draw_mandelbrot complet\n", getpid());
}
