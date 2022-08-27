/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 06:33:56 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/27 06:16:29 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	frac_update(t_super *sup)
{
	t_img	*buff;

	buff = sup->mlx->off_buff;
	ft_memclear(buff->addr, sup->mlx->buff_size);
	draw_mandelbrot(buff, &sup->frm);
	if (mlx_render_buffer(sup->mlx) < 0)
		on_close(sup, EXIT_WERROR, EXIT_MLX_RENDERING_FAILED);
}
