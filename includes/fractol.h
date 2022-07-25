/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:20:21 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/25 00:33:49 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <complex.h>

# include "mlx.h"
# include "mlxadds.h"
# include "keycodes.h"
# include "libft.h"

# define NB_DRAWING_PROCS 8

# define TRGT_SCN_HEIGHT 400

//# define SCN_HEIGHT TRGT_SCN_HEIGHT + (TRGT_SCN_HEIGHT % NB_DRAWING_PROCS)
# define SCN_HEIGHT TRGT_SCN_HEIGHT
# define SCN_WIDTH 400
# define SCN_MIDX (double)(SCN_WIDTH / 2)
# define SCN_MIDY (double)(SCN_HEIGHT / 2)
# define ASPECT_RATIO SCN_WIDTH / SCN_HEIGHT
# define FRM_WIDTH 4.0f
# define FRM_HEIGHT 4.0f
# define MAX_ITER 100
# define INIT_ZOOM 1
# define ZOOM_INCREMENT 0.05
# define INIT_POSX 0
# define INIT_POSY 0
# define MOVE_INCREMENT 0.1

# define BAILOUT_DIST INT_MAX//(1 << 32)

# define NBCOLS 7

//PROCESS DEFINES
# define DRAWN_Y_RANGE (SCN_HEIGHT / 8)
# define DRAWN_AREA_NB_BYTES (DRAWN_Y_RANGE * SCN_WIDTH)

typedef struct	s_mandelbrot_frame
{
	int	instruction;
	t_mlx	*mlx;
	double	zoom;
	double	px;
	double	py;
	int	palette[NBCOLS][3];
}	t_frm;

typedef struct	s_pixel
{
	int		sx;
	int		sy;
	double		fx;
	double		fy;
	double complex	z;
	int		*palette;
}	t_pix;

enum	e_process_status
{
	P_STOPPED = 0,
	P_ERROR = -1,
	P_WAITING = 1,
	P_DRAWING = 2,
	P_DONE = 3
};

enum	e_drawing_instructions
{
	S_STOP,
	S_DRAW
};

// Process pool data held by main process
typedef struct	s_process_pool
{
	int	pids[NB_DRAWING_PROCS];
	int	status[NB_DRAWING_PROCS]; // 1: live 0: finished/not started, -1: error;
	int	rd_pipes[NB_DRAWING_PROCS];
	int	wr_pipes[NB_DRAWING_PROCS];
}	t_pool;

// drawing instruction package sent to children
typedef struct	s_process_pkg
{
	int	p_index;
	int	pp[2];
}	t_ppkg;

void	convert_pix_to_frame(t_frm *frm, t_pix *pix);
void	draw_mandelbrot(t_mlx *mlx, t_frm *frm);
double	mandelbrot_dist(t_pix *pix, int *iters);
void	frac_move_frame(t_frm *frm, double deltaX, double deltaY);
void	frac_zoom(t_frm *frm, double increment);
void	frac_update(t_frm *frm);

t_frm	*init_base_color_palette(t_frm *frm);

#endif
