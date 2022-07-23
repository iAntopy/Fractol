/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:20:21 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/23 00:04:31 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACORL_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <complex.h>

# include "mlx.h"
# include "mlxadds.h"
# include "keycodes.h"

# define SCN_WIDTH 100 
# define SCN_HEIGHT 100
# define SCN_MIDX (double)(SCN_WIDTH / 2)
# define SCN_MIDY (double)(SCN_HEIGHT / 2)
# define FRM_WIDTH 4.0f
# define FRM_HEIGHT 4.0f
# define MAX_ITER 10
# define INIT_ZOOM 1
# define ZOOM_INCREMENT 0.01
# define INIT_POSX 0
# define INIT_POSY 0
# define MOVE_INCREMENT 0.1

typedef struct	s_mandelbrot_frame
{
	t_mlx	*mlx;
	double	zoom;
	double	px;
	double	py;
}	t_frm;

typedef struct	s_pixel
{
	int				sx;
	int				sy;
	double			fx;
	double			fy;
	double complex	z;
}	t_pix;

void	draw_mandelbrot(t_mlx *mlx, t_frm *frm);

#endif
