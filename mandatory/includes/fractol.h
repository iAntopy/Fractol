/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:20:21 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/27 08:00:03 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "fractol_core.h"

typedef struct s_super
{
	t_mlx	*mlx;
	t_frm	frm;
	int		mouse_1_pressed;
	int		mouse_1_dragging;
	int		mouse_3_pressed;
	int		mouse_3_dragging;
	int		last_x;
	int		last_y;
}	t_super;

void	draw_mandelbrot(t_img *buff, t_frm *frm);

#endif
