/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_clear_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 02:09:01 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/05 02:27:58 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxadds.h"

void	mlx_clear_buffer(t_mlx *mlx)
{
	size_t	*b;
	size_t	total_bytes;
	size_t	s;
	char	*c;

	total_bytes = mlx->buff1.line_len * mlx->height;
	b = (size_t *)mlx->off_buff->addr;
	s = sizeof(size_t);
	while (total_bytes >= s)
	{
		*b = 0;
		b++;
		total_bytes -= s;
	}
	c = (char *)b;
	while (total_bytes--)
		*c = 0;
}
