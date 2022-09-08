/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_buffers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 23:04:27 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/25 19:41:40 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlxadds.h"

// pushes screen_buff to window and swaps buffers for next draw.
int	mlx_render_buffer(t_mlx *mlx)
{
	mlx_swap_buffers(mlx);
	return (mlx_put_image_to_window(mlx->conn,
			mlx->win, mlx->scn_buff->img,
			0, 0));
}
