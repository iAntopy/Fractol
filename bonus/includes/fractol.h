/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:20:21 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/27 08:00:25 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <signal.h>
# include <sys/mman.h>

# include "fractol_core.h"

# define NB_DRAWING_PROCS 8

// LOOP ANIMATION
# define FPS 60
# define MV_THLD 5
# define ZM_THLD 0.1
# define RT_THLD 0.031415
# define JL_THLD 0.002
# define SMOOTHNESS 20// nb of subdivisions of a movement. (Higher is smoother.)

/*
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
	double			cx;
	double			cy;
	double			dist;
	int				iters;
}	t_pix;

typedef	t_pix	*(t_dist_func)(t_pix *);

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
	EXIT_SHARED_MEM_FAILED,
	EXIT_PARSING_FAILED,
	EXIT_BROKEN_POOL,
	EXIT_FORCED_CLOSE
};
*/
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
	char	buff1_data[(SCN_WIDTH + 32) * (SCN_HEIGHT + 4) * sizeof(int)];
	char	buff2_data[(SCN_WIDTH + 32) * (SCN_HEIGHT + 4) * sizeof(int)];
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
typedef struct s_super
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
	size_t	update_delay;
}	t_super;

// FUNCTION PROTOTYPES
int		on_update(t_super *sup);
void	frac_stop_animation(t_super *sup);
void	draw_mandelbrot(t_img *buff, t_frm *frm, int y_start, int y_end);

// EVENT SWITCHES
int		frac_key_switch(int keycode, t_super *sup);

// DRAW POOL FUNCTIONS
int		init_process_pool(t_pool *pool, t_shmem *sm);
int		close_process_pool(t_pool *pool, char *err_msg);
int		force_close_process_pool(t_pool *pool, char *err_msg);
int		order_pool_draw(t_pool *pool, t_shmem *sm);

#endif
