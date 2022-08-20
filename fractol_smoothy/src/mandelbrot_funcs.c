/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:27:04 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/20 06:43:47 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_pix_color(int *pal, int nb_cols, double dist, int iters)
{
	int		*pcols[2];
	int		colors[3];
	double	interpol;
	double	norm_iters;

	norm_iters = (nb_cols - 1) * ((double)iters - log(log(dist) / 10));
	norm_iters /= MAX_ITER;
	iters = (int)norm_iters;
	interpol = norm_iters - iters;
	pcols[0] = pal + (iters * 3);
	pcols[1] = pcols[0] + 3;
	colors[0] = (int)(pcols[0][0] + (pcols[1][0] - pcols[0][0]) * interpol);
	colors[1] = (int)(pcols[0][1] + (pcols[1][1] - pcols[0][1]) * interpol);
	colors[2] = (int)(pcols[0][2] + (pcols[1][2] - pcols[0][2]) * interpol);
	return ((colors[0] << 16) | (colors[1] << 8) | colors[2]);
}

void	draw_mandelbrot(t_img *buff, t_frm *frm, int y_start, int y_end)
{
	t_pix	pix;
	int		x;
	int		y;
	int		color;

	pix.cx = frm->cx;
	pix.cy = frm->cy;
	y = y_start - 1;
	while (++y < y_end)
	{
		pix.sy = y;
		x = -1;
		while (++x < SCN_WIDTH)
		{
			pix.sx = x;
			convert_pix_to_frame(frm, &pix);
			frm->dist_func(&pix);
			if ((pix.dist > 2) && (pix.iters < MAX_ITER))
			{
				color = get_pix_color((int *)frm->pal.palette,
						frm->pal.nb_cols, pix.dist, pix.iters);
				mlx_buff_put_pixel(buff, x, y, color);
			}
		}
	}
}
