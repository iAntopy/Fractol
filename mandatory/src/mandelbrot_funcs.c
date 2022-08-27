/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:27:04 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/27 08:06:08 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_pix_color(int *pal, int nb_cols, double dist, int iters)
{
	int		*col1;
	int		*col2;
	double	interpol;
	double	norm_iters;
	int		res_color;

	norm_iters = (nb_cols - 1) * ((double)iters - log(log(dist) / 10));
	norm_iters /= MAX_ITER;
	iters = (int)norm_iters;
	interpol = norm_iters - iters;
	col1 = pal + (iters * 3);
	col2 = col1 + 3;
	res_color = (int)(*col1 + (*col2 - *col1) * interpol) << 16;
	col1++;
	col2++;
	res_color |= (int)(*col1 + (*col2 - *col1) * interpol) << 8;
	col1++;
	col2++;
	res_color |= (int)(*col1 + (*col2 - *col1) * interpol);
	return (res_color);
}

void	draw_mandelbrot(t_img *buff, t_frm *frm)
{
	t_pix	pix;
	int		x;
	int		y;
	int		color;

	pix.cx = frm->cx;
	pix.cy = frm->cy;
	y = -1;
	while (++y < SCN_HEIGHT)
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
