/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:20:21 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/07 16:16:50 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <complex.h>
# include <signal.h>

# include "mlx.h"
# include "mlxadds.h"
# include "keycodes.h"
# include "libft.h"

# define SCN_WIDTH 640// CHANGE HERE
# define SCN_HEIGHT 480// CHANGE HERE

# define SCN_MIDX ((double)SCN_WIDTH / 2)
# define SCN_MIDY ((double)SCN_HEIGHT / 2)
# define ASP_RATIO ((double)SCN_HEIGHT / SCN_WIDTH)
# define MAX_ITER 100 
# define INIT_ZOOM (3.0f / SCN_HEIGHT)//1.0f
# define ZOOM_INCREMENT 0.5
# define INIT_POSX 0.0f
# define INIT_POSY 0.0f
# define MOVE_INCREMENT 0.1
# define INIT_ANGLE 0
# define ROT_INCREMENT (2 * M_PI / 32)

# define C_REAL 0
# define C_IMAG 0.297
# define JULIA_INCREMENT 0.1
# define BAILOUT_DIST INT_MAX//(1 << 32)

//PROCESS DEFINES
//# define DRAWN_Y_RANGE (SCN_HEIGHT / NB_DRAWING_PROCS)
//# define DRAWN_Y_BYTES (SCN_HEIGHT / NB_DRAWING_PROCS)
//# define DRAWN_LAST_Y_RANGE SCN_HEIGHT - ((NB_DRAWING_PROCS - 1) * DRAWN_Y_RANGE)

//# define DRAWN_AREA_NB_PIX (DRAWN_Y_RANGE * SCN_WIDTH)
//# define DRAWN_AREA_NB_BYTES (DRAWN_AREA_NB_PIX * sizeof(int))
//# define DRAWN_LAST_AREA_NB_BYTES (DRAWN_LAST_Y_RANGE * SCN_WIDTH)

typedef struct	s_palette
{
	int	pal_code;
	int	nb_cols;
	int	palette[10][3];
}	t_pal;

typedef struct	s_pixel
{
	int		sx;
	int		sy;
	double		fx;
	double		fy;
	double complex	z;
	double		cx;
	double		cy;
	int		nb_cols;
	double		dist;
	int		iters;
	int		*palette;
}	t_pix;

typedef t_pix *(*DIST_FUNC)(t_pix *);

typedef struct	s_mandelbrot_frame
{
	double		zoom;
	double		px;
	double		py;
	double		ang;
//	double complex	c;
	double		cx;
	double		cy;
	t_pal		pal;
	DIST_FUNC	dist_func;
}	t_frm;

enum	e_palette_codes
{
	PALETTE_MIAMI,
	PALETTE_MONOCHROME,
	PALETTE_ORANGE,
	PALETTE_GREEN
};

// containes all major sub structures for global management
typedef struct	s_super_struct
{
	t_mlx	*mlx;
	t_frm	*frm;
}	t_super;

// FUNCTION PROTOTYPES
void	convert_pix_to_frame(t_frm *frm, t_pix *pix, int print);
void	draw_mandelbrot(t_img *buff, t_frm *frm);

// CORE EVENTS
int	on_close(t_super *sup);

// EVENT SWITCHS
int	frac_mouse_click(int button, int x, int y, t_super *sup);
int	frac_key_switch(int keycode, t_super *sup);

void	frac_move_frame(t_super *sup, double deltaX, double deltaY);
void	frac_set_frame_pos(t_super *sup, double x, double y);
void	frac_zoom(t_super *sup, double increment);
void	frac_dir_zoom(t_super *sup, double x, double y, double increment);
void	frac_rotate(t_super *sup, double increment);
void	frac_reset_frame(t_super *sup);
void	frac_shift_julia(t_super *sup, double real, double imag);
void	switch_color_palette(t_super *sup);
void	switch_color_julia_mandelbrot_mode(t_super *sup);
void	frac_update(t_super *sup);

void	init_base_color_palette(t_pal *pal, int pal_code);
void	give_mandelbrot_coord_rundown(t_pix *pix, t_frm *frm);

t_pix	*mandelbrot_dist(t_pix *pix);
t_pix	*julia_dist(t_pix *pix);
t_pix	*burning_ship_dist(t_pix *pix);

void	close_fd_ptr_list(int nb_fds, ...);
#endif
