/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_buff_put_pixel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:50:46 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/04 23:10:03 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxadds.h"

void	mlx_buff_put_pixel(t_img *buff, int x, int y, int color)
{
	char	*pix;
	
	pix = buff->addr + (y * buff->line_len) + (x * buff->bytes_per_pxl);
	*(unsigned int *)pix = color;
}
