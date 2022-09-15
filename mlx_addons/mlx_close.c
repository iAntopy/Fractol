/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:24:57 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/14 22:33:45 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxadds.h"

#ifdef __APPLE__

void	mlx_close(t_mlx *mlx)
{
	if (mlx->scn_buff)
		mlx_destroy_image(mlx->conn, mlx->scn_buff->img);
	if (mlx->off_buff)
		mlx_destroy_image(mlx->conn, mlx->off_buff->img);
	mlx->scn_buff = NULL;
	mlx->off_buff = NULL;
	mlx_destroy_window(mlx->conn, mlx->win);
	ft_printf("mlx_close : mlx close SUCCESSFUL !\n");
}

#elif __linux__

void	mlx_close(t_mlx *mlx)
{
	if (mlx->scn_buff)
		mlx_destroy_image(mlx->conn, mlx->scn_buff->img);
	if (mlx->off_buff)
		mlx_destroy_image(mlx->conn, mlx->off_buff->img);
	mlx->scn_buff = NULL;
	mlx->off_buff = NULL;
	mlx_destroy_window(mlx->conn, mlx->win);
	mlx_destroy_display(mlx->conn);
	ft_printf("mlx_close : mlx close SUCCESSFUL !\n");
}
#endif
