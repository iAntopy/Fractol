/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_set_bg_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 02:31:10 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/05 02:40:37 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxadds.h"

void	mlx_set_bg_color(t_mlx *mlx, int col)
{
	int	*b;
	int	nb_pxl;

	b = (int *)mlx->off_buff->addr;
	nb_pxl = mlx->width * mlx->height;
	while (nb_pxl--)
		*(b++) = col;
}
