/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:20:21 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/20 08:33:19 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <complex.h>
# include <signal.h>
# include <sys/mman.h>

# include "mlx.h"
# include "mlxadds.h"
# include "keycodes.h"
# include "libft.h"

# define __SCN_WIDTH 1280// CHANGE SCREEN WIDTH HERE
# define __SCN_HEIGHT 1024// CHANGE SCREEN HEIGHT HERE

# define NB_DRAWING_PROCS 8

# define SCN_WIDTH (__SCN_WIDTH + (__SCN_WIDTH % NB_DRAWING_PROCS))
# define SCN_HEIGHT (__SCN_HEIGHT + (__SCN_HEIGHT % 2))
# define SCN_MIDX ((double)SCN_WIDTH / 2)
# define SCN_MIDY ((double)SCN_HEIGHT / 2)
# define MAX_ITER 200
# define INIT_ZOOM (4.0f / SCN_HEIGHT)
# define ZOOM_INCREMENT 0.5
# define INIT_POSX 0.0f
# define INIT_POSY 0.0f
# define MOVE_INCREMENT 10.0f
# define INIT_ANGLE 0.0f
# define ROT_INCREMENT (2 * M_PI / 32)
# define INIT_CREAL 0.0f
# define INIT_CIMAG 0.0f
# define JULIA_INCREMENT 0.05f

# define BAILOUT_DIST INT_MAX

// LOOP ANIMATION
# define FPS 30
# define FRAME_USEC (1.0f / FPS * 1000000)
# define MV_THLD 5
# define ZM_THLD 0.1
# define RT_THLD 0.031415
# define JL_THLD 0.002
# define SMOOTHNESS 20// nb of subdivisions of a movement. (Higher is smoother.)

//PROCESS DEFINES
# define DRAWN_Y_RANGE (SCN_HEIGHT / NB_DRAWING_PROCS)
# define BUFFER_SIZE ((SCN_WIDTH + 32) * (SCN_HEIGHT + 4) * sizeof(int))

typedef struct s_palette
{
	int	pal_code;
	int	nb_cols;
	int	palette[10][3];
}	t_pal;

typedef struct s_pixel
{
	double			sx;
	double			sy;
	double			fx;
	double			fy;
	double complex	z;
	double			cx;
	double			cy;
	double			dist;
	int				iters;
}	t_pix;

typedef	t_pix	*(t_dist_func)(t_pix *);

typedef struct s_mandelbrot_frame
{
	double		zoom;
	double		px;
	double		py;
	double		cx;
	double		cy;
	double		ang;
	t_pal		pal;
	t_dist_func	*dist_func;
}	t_frm;

enum	e_process_status
{
	P_STOPPED = 0,
	P_ERROR = -1,
	P_WAITING = 1,
	P_DRAWING = 2,
	P_DONE = 3
};

enum	e_pool_status
{
	STATUS_RUNNING = 0,
	STATUS_CLOSED = 1,
	STATUS_BROKEN = 2
};

enum	e_drawing_instructions
{
	SIG_TERM = SIGTERM,
	SIG_DRAW = SIGUSR1
};

enum	e_palette_codes
{
	PALETTE_MIAMI,
	PALETTE_MONOCHROME,
	PALETTE_ORANGE,
	PALETTE_GREEN
};

enum	e_exit_codes
{
	EXIT_SHARED_MEM_FAILED,
	EXIT_PARSING_FAILED,
	EXIT_BROKEN_POOL,
	EXIT_FORCED_CLOSE
};

// sfrm is the current screen frame displayed on screen.
// draw_buff is a pointer to either buff1 or buff2. 
// draw_buff swaps between the two before ordering pool to draw.
typedef struct s_shared_mem_mproc_double_buff
{
	t_frm	sfrm;
	int		proc_draw_done[NB_DRAWING_PROCS];
	t_img	*draw_buff;
	t_img	buff1;
	t_img	buff2;
	char	buff1_data[BUFFER_SIZE];
	char	buff2_data[BUFFER_SIZE];
}	t_shmem;

// Process pool data held by main process
typedef struct s_process_pool
{
	int	pool_status;
	int	pids[NB_DRAWING_PROCS];
}	t_pool;

// Containes all major sub structures for global management.
// frm here is the target frame controled by user. The update loop
// will work to render the animation between current screen frame and 
// target frame. After every user input, the needs_update flag will be
// raised and the on_update function will update on next frame.
typedef struct s_super_struct
{
	t_mlx	*mlx;
	t_pool	*pool;
	t_frm	frm;
	t_shmem	*shmem;
	int		needs_update;
	int		mouse_1_pressed;
	int		mouse_3_pressed;
	int		mouse_1_dragging;
	int		mouse_3_dragging;
	int		last_x;
	int		last_y;
}	t_super;

// FUNCTION PROTOTYPES
int		parse_inputs(t_frm *frm, int argc, char **argv);
int		on_close(t_super *sup);
int		on_update(t_super *sup);
void	draw_mandelbrot(t_img *buff, t_frm *frm, int y_start, int y_end);
void	frac_update(t_super *super);
void	init_base_color_palette(t_pal *pal, int pal_code);
void	frac_shift_julia(t_super *sup, double real, double imag);
void	frac_set_julia_shift(t_super *sup, double real, double imag);

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
void	frac_stop_animation(t_super *sup);
void	reset_frame(t_frm *frm);
void	init_frame(t_frm *frm);

// EVENT SWITCHES
int		frac_key_switch(int keycode, t_super *sup);

// MOUSE EVENT MANAGERS
int		init_mouse_data(t_super *sup);
int		on_mouse_release(int button, int x, int y, t_super *sup);
int		on_mouse_press(int button, int x, int y, t_super *sup);
int		on_mouse_drag(int x, int y, t_super *sup);

// DRAW POOL FUNCTIONS
int		init_process_pool(t_pool *pool, t_shmem *sm);
int		close_process_pool(t_pool *pool, char *err_msg);
int		force_close_process_pool(t_pool *pool, char *err_msg);
int		order_pool_draw(t_pool *pool, t_shmem *sm);

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
