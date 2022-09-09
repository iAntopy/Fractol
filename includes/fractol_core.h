/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_core.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:47:53 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/09 02:11:23 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_CORE_H
# define FRACTOL_CORE_H

# include <math.h>

# include "mlx.h"
# include "mlxadds.h"
# include "keycodes.h"
# include "libft.h"

# define SCN_WIDTH 1280
# define SCN_HEIGHT 1024

# define MAX_ITER 200
# define ZOOM_INCREMENT 0.5f
# define INIT_POSX 0.0f
# define INIT_POSY 0.0f
# define MOVE_INCREMENT 10
# define INIT_ANGLE 0.0f
# define ROT_INCREMENT 0.2f
# define INIT_CREAL 0.0f
# define INIT_CIMAG 0.0f
# define JULIA_INCREMENT 0.05f

# define BAILOUT_DIST INT_MAX

typedef struct s_palette
{
	int	pal_code;
	int	nb_cols;
	int	palette[10][3];
}	t_pal;

typedef struct s_pixel
{
	double	sx;
	double	sy;
	double	fx;
	double	fy;
	double	cx;
	double	cy;
	double	dist;
	int		iters;
}	t_pix;

typedef					t_pix *(t_dist_func)(t_pix *);
typedef struct s_super	t_super;

typedef struct s_mandelbrot_frame
{
	int			scn_midx;
	int			scn_midy;
	double		zoom;
	double		px;
	double		py;
	double		cx;
	double		cy;
	double		ang;
	double		cos_a;
	double		sin_a;
	t_pal		pal;
	t_dist_func	*dist_func;
}	t_frm;

enum	e_palette_codes
{
	PALETTE_MIAMI,
	PALETTE_MONOCHROME,
	PALETTE_ORANGE,
	PALETTE_GREEN
};

enum	e_exit_codes
{
	EXIT_NORMAL = 0,
	EXIT_WERROR = -42,
	EXIT_MLX_RENDERING_FAILED,
	EXIT_SHARED_MEM_FAILED,
	EXIT_PARSING_FAILED,
	EXIT_POOL_TIMEOUT,
	EXIT_BROKEN_POOL,
	EXIT_FORCED_CLOSE
};

// FUNCTION PROTOTYPES
int		parse_inputs(t_frm *frm, int argc, char **argv);
int		on_close(t_super *sup, int has_failed, int exit_code);
void	frac_update(t_super *super);
void	init_base_color_palette(t_pal *pal, int pal_code);
void	frac_shift_julia(t_super *sup, double real, double imag);
void	frac_set_julia_shift(t_super *sup, int x, int y);

// SCREEN TO FRAME CONVERTER FUNCTIONS 
void	convert_pix_to_frame(t_frm *frm, t_pix *pix);
void	convert_vect_to_frame(t_frm *frm, t_pix *pix);

// MOVE FRAME FUNCTIONS
void	frac_move_frame(t_super *sup, double deltaX, double deltaY);
void	frac_set_frame_pos(t_super *sup, double x, double y);
void	frac_zoom(t_super *super, double increment);
void	frac_dir_zoom(t_super *sup, double x, double y, double increment);
void	frac_rotate(t_super *sup, double increment);
void	frac_reset_frame(t_super *sup);
t_frm	*reset_frame(t_frm *frm);
t_frm	*init_frame(t_frm *frm);

// EVENT SWITCHES
int		frac_key_switch(int keycode, t_super *sup);

// MOUSE EVENT MANAGERS
int		init_mouse_data(t_super *sup);
int		on_mouse_release(int button, int x, int y, t_super *sup);
int		on_mouse_press(int button, int x, int y, t_super *sup);
int		on_mouse_drag(int x, int y, t_super *sup);

// DIST FUNCTIONS
t_pix	*mandelbrot_dist(t_pix *pix);
t_pix	*julia_dist(t_pix *pix);
t_pix	*burning_ship_dist(t_pix *pix);
t_pix	*burning_ship_julia_dist(t_pix *pix);
t_pix	*celtic_dist(t_pix *pix);
t_pix	*celtic_julia_dist(t_pix *pix);
t_pix	*temple_dist(t_pix *pix);
t_pix	*temple_julia_dist(t_pix *pix);
t_pix	*crown_dist(t_pix *pix);
t_pix	*crown_julia_dist(t_pix *pix);
t_pix	*cupid_dist(t_pix *pix);
t_pix	*cupid_julia_dist(t_pix *pix);
t_pix	*mandelbrot_5th_order_dist(t_pix *pix);
t_pix	*julia_5th_order_dist(t_pix *pix);

#endif
