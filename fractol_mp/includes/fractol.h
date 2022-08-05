/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:20:21 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/04 20:26:49 by iamongeo         ###   ########.fr       */
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
# define __SCN_HEIGHT 720// CHANGE SCREEN HEIGHT HERE

# define NB_DRAWING_PROCS 8

//# define SCN_HEIGHT TRGT_SCN_HEIGHT + (TRGT_SCN_HEIGHT % NB_DRAWING_PROCS)
# define SCN_WIDTH (__SCN_WIDTH + (__SCN_WIDTH % NB_DRAWING_PROCS))
# define SCN_HEIGHT (__SCN_HEIGHT + (__SCN_HEIGHT % 2))
# define SCN_MIDX ((double)SCN_WIDTH / 2)
# define SCN_MIDY ((double)SCN_HEIGHT / 2)
//# define ASP_RATIO ((double)SCN_HEIGHT / SCN_WIDTH)
//# define FRM_WIDTH 4.0f
//# define FRM_HEIGHT ASP_RATIO * FRM_WIDTH//4.0f
# define MAX_ITER 300 
# define INIT_ZOOM (4.0f / SCN_HEIGHT)
# define ZOOM_INCREMENT 0.05
# define INIT_POSX 0.0f
# define INIT_POSY 0.0f
# define MOVE_INCREMENT 0.1
# define INIT_ANGLE 0
# define ROT_INCREMENT (2 * M_PI / 256)

# define BAILOUT_DIST INT_MAX

# define NBCOLS 7

//PROCESS DEFINES
# define DRAWN_Y_RANGE (SCN_HEIGHT / NB_DRAWING_PROCS)
//# define DRAWN_Y_BYTES (SCN_HEIGHT / NB_DRAWING_PROCS)
//# define DRAWN_LAST_Y_RANGE SCN_HEIGHT - ((NB_DRAWING_PROCS - 1) * DRAWN_Y_RANGE)

# define BUFFER_SIZE ((SCN_WIDTH + 32) * (SCN_HEIGHT + 4) * sizeof(int))
//# define DRAWN_LAST_AREA_NB_BYTES (DRAWN_LAST_Y_RANGE * SCN_WIDTH)

# ifndef MULTIPROC_RENDERING
#  define MULTIPROC_RENDERING 1
# endif

typedef struct	s_mandelbrot_frame
{
	double	zoom;
	double	px;
	double	py;
	double	ang;
	int		palette[NBCOLS][3];
//	t_mlx	*mlx;
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

// extra mem allocation at end of lines + extra line to comply with xserver buffer formating.
// mem unused if OpenGL used.
typedef struct	s_shared_mem_mproc_double_buff
{
	t_frm	frm;
	int		proc_draw_done[NB_DRAWING_PROCS];
	t_img	*draw_buff;	//PTR TO ONE OF THE BUFFERS BELOW IN WHICH TO DRAW
	t_img	buff1;
	t_img	buff2;
	char	buff1_data[BUFFER_SIZE];//(SCN_WIDTH + 32) * (SCN_HEIGHT + 4) * sizeof(int)];
	char	buff2_data[BUFFER_SIZE];//(SCN_WIDTH + 32) * (SCN_HEIGHT + 4) * sizeof(int)];
}	t_shmem;

// Process pool data held by main process
typedef struct	s_process_pool
{
	int	pool_status;
	int	pids[NB_DRAWING_PROCS];
}	t_pool;
/*
// drawing instruction package sent to children
typedef struct	s_process_pkg
{
	int	p_index;
	int	instruction;//SIG_DRAW, SIG_STOP
	int	pp[2];
}	t_ppkg;
*/


// containes all major sub structures for global management
typedef struct	s_super_struct
{
	t_mlx	*mlx;
	t_pool	*pool;
	t_frm	*frm;
	t_shmem	*shmem;
	int		multiproc;
}	t_super;


// FUNCTION PROTOTYPES
void	convert_pix_to_frame(t_frm *frm, t_pix *pix, int print);
//void	draw_mandelbrot(t_mlx *mlx, t_frm *frm);
void	draw_mandelbrot(t_img *buff, t_frm *frm, int y_start, int y_end);
double	mandelbrot_dist(t_pix *pix, int *iters);
void	frac_move_frame(t_super *super, double deltaX, double deltaY);
void	frac_zoom(t_super *super, double increment);
void	frac_rotate(t_super *sup, double increment);
void	frac_update(t_super *super);
void	frac_update_multiprocessor(t_super *super);

t_frm	*init_base_color_palette(t_frm *frm);

// DRAW POOL FUNCTIONS
int	init_process_pool(t_pool *pool, t_shmem *sm);//, t_frm *frm);
int	close_process_pool(t_pool *pool, char *err_msg);
int	force_close_process_pool(t_pool *pool, char *err_msg);
int	order_pool_draw(t_pool *pool, t_shmem *sm);//t_frm *frm, t_mlx *mlx);

void	close_fd_ptr_list(int nb_fds, ...);
#endif
