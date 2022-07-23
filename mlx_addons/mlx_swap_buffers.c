/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_swap_buffers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 21:19:22 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/04 23:13:14 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlxadds.h"

int	mlx_swap_buffers(t_mlx *mlx)
{
	t_img	*temp;

	temp = mlx->screen_buff;
	mlx->screen_buff = mlx->off_buff;
	mlx->off_buff = temp;
//	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->screen_buff->img, 0, 0);
	return (1);
}
