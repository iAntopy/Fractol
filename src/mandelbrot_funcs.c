/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:27:04 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/08 21:07:02 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
void	convert_pix_to_frame(t_frm *frm, t_pix *pix, int print)
{
	double	cos_ang;
	double	sin_ang;
	double	fx;
	double	fy;

	(void)print;
//	if (print)
//	{
//		printf("converting starts :\n");
///		printf("zoom %f, sx %i, sy %i\n", frm->zoom, pix->sx, pix->sy);
//	}

	cos_ang = cos(frm->ang);
	sin_ang = sin(frm->ang);
	fx = pix->sx - SCN_MIDX;
	fy = pix->sy - SCN_MIDY;
	pix->fx = frm->zoom * (cos_ang * fx + sin_ang * fy) + frm->px;
	pix->fy = frm->zoom * (-sin_ang * fx + cos_ang * fy) + frm->py;
//	if (print)
//		printf("converted coords : x %f, y %f\n", pix->fx, pix->fy);
}
*/
/*
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
	pix->fx = frm->zoom * (cos_ang * fx + sin_ang * fy);
	pix->fy = frm->zoom * (-sin_ang * fx + cos_ang * fy);
	printf("convert vect : fx, fy :  (%f, %f)\n", pix->fx, pix->fy);
}
*/
static int	get_mandelbrot_pix_color(t_pix *pix, double dist, int iters, int print)
{
	int	*pcols[2];
	int	colors[3];
	int	color;
	double	interpolation;
	double	norm_iters;
//	double	ratio;
//	int	i_iters;
//	double	red_ratio;
//	double	green_ratio;
//	double	blue_ratio;
	
//	ratio = 2 / (1 + exp(-0.01 * (1 / (dist - 2)))) + 1;
//	ratio = 2 / (1 + exp(-0.1 * (1 / (dist - 2)))) + 1;
	norm_iters = (pix->nb_cols - 1) * ((double)iters - log(log(dist) / 10)) / MAX_ITER;
//	ratio = norm_iters / MAX_ITER;
	iters = (int)norm_iters;
	interpolation = norm_iters - iters;
//	if (iters == 1)
//	{
///		printf("\n\n\n WATCH OUT : iters too big : %d\n", iters);
///		printf("iters %d, norm_iters %f \n", iters, norm_iters);
///		printf("dist %f, BAILOUT DIST %d, interpolation %f\n", dist, BAILOUT_DIST, interpolation);
//	}
//	ratio = 1 / dist;
//	red_ratio = ratio;
//	green_ratio = ratio;
//	blue_ratio = ratio;
//	if (color_ratio > 1)
//		color_ratio = 1;
//	color = 0x00ffffff * ratio;
//	if (print)
//	{
///		printf("\niters %d, norm_iters %f \n", iters, norm_iters);
//		printf("dist %f, interpolation %f\n", dist, interpolation);
//	}
	pcols[0] = pix->palette + (iters * 3);
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

void	draw_mandelbrot(t_img *buff, t_frm *frm)
{
	t_pix	pix;
	int		x;
	int		y;
	int		color;

	pix.cx = frm->cx;
	pix.cy = frm->cy;
	pix.nb_cols = frm->pal.nb_cols;
	pix.palette = (int *)frm->pal.palette;
//	printf("Corner color in frame : r %d g %d b %d \n", frm->palette[0][0], frm->palette[0][1], frm->palette[0][2]);
	
	y = -1;
	while (++y < SCN_HEIGHT)
	{
//		printf("drawing line %d\n", y);
		x = -1;
		while (++x < SCN_WIDTH)
		{
			pix.sx = x;
			pix.sy = y;
			convert_pix_to_frame(frm, &pix, (!y && !x));
			frm->dist_func(&pix);
//			mandelbrot_dist(&pix, frm->c);
			if ((pix.dist > 2) && (pix.iters < MAX_ITER))
			{
				color = get_mandelbrot_pix_color(&pix, pix.dist, pix.iters, (!y && !x));
				mlx_buff_put_pixel(buff, x, y, color);
//				mlx_buff_put_pixel(buff, x + 1, y, color);
//				mlx_buff_put_pixel(buff, x, y + 1, color);
//				mlx_buff_put_pixel(buff, x + 1, y + 1, color);
//				arr[(y - y_start) * SCN_WIDTH + x] = color;
			}
//			x += 2;
		}
//		y += 2;
	}
	printf("pid %d draw_mandelbrot complet\n", getpid());
}
