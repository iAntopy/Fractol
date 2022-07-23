/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_buffers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 23:04:27 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/22 23:13:49 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlxadds.h"

// pushes screen_buff to window and swaps buffers for next draw.
void	mlx_render_buffer(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->screen_buff, 0, 0);
	mlx_swap_buffers(mlx);
}
