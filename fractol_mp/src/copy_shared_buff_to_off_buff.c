/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_shmem_buffer_to_off_buff.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:58:09 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/03 18:06:30 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_mlx	*copy_shared_buff_to_off_buff(t_mlx *mlx, t_shmem *sm)
{
	if (!(mlx && sm))
		return (NULL);
	ft_memcpy(mlx->off_buff->addr, sm->draw_buff, mlx->buff_size);
	return (mlx);
}
