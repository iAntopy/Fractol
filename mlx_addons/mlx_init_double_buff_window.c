/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_double_buff_window.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 04:01:40 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/14 22:41:20 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxadds.h"

static int	init_screen_buffers(t_mlx *mlx, t_img *b1, t_img *b2)
{
	b1->img = mlx_new_image(mlx->conn, mlx->width, mlx->height);
	b2->img = mlx_new_image(mlx->conn, mlx->width, mlx->height);
	if (!b1->img || !b2->img)
		return (0);
	b1->addr = mlx_get_data_addr(b1->img, &b1->bytes_per_pxl,
			&b1->line_len, &b1->endian);
	b2->addr = mlx_get_data_addr(b2->img, &b2->bytes_per_pxl,
			&b2->line_len, &b2->endian);
	b1->bytes_per_pxl /= 8;
	b2->bytes_per_pxl /= 8;
	mlx->scn_buff = &mlx->buff1;
	mlx->off_buff = &mlx->buff2;
	mlx->nb_pix = mlx->width * mlx->height;
	mlx->buff_size = b1->line_len * mlx->height;
	return (1);
}

//Declare a t_mlx variable in main and pass its pointer to this function.
t_mlx	*mlx_init_double_buff_window(t_mlx *mlx, int wdt, int hgt, char *title)
{
	mlx->conn = mlx_init();
	if (!mlx->conn)
	{
		fperror("Pass the ptr to a t_mlx struct declared in main as 1st arg.");
		return (NULL);
	}
	mlx->win = mlx_new_window(mlx->conn, wdt, hgt, title);
	if (!mlx->win)
		return (NULL);
	mlx->width = wdt;
	mlx->height = hgt;
	mlx_clear_window(mlx->conn, mlx->win);
	init_screen_buffers(mlx, &mlx->buff1, &mlx->buff2);
	return (mlx);
}
