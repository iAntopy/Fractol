/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:20:21 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/02 16:51:02 by iamongeo         ###   ########.fr       */
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

# define __SCN_WIDTH 640// CHANGE HERE
# define __SCN_HEIGHT 480// CHANGE HERE

# define NB_DRAWING_PROCS 2

//# define SCN_HEIGHT TRGT_SCN_HEIGHT + (TRGT_SCN_HEIGHT % NB_DRAWING_PROCS)
# define SCN_WIDTH (__SCN_WIDTH + (__SCN_WIDTH % NB_DRAWING_PROCS))
# define SCN_HEIGHT (__SCN_HEIGHT + (__SCN_HEIGHT % 2))
# define SCN_MIDX ((double)SCN_WIDTH / 2)
# define SCN_MIDY ((double)SCN_HEIGHT / 2)
# define ASP_RATIO ((double)SCN_HEIGHT / SCN_WIDTH)
# define FRM_WIDTH 4.0f
# define FRM_HEIGHT ASP_RATIO * FRM_WIDTH//4.0f
# define MAX_ITER 300 
# define INIT_ZOOM 1.0f
# define ZOOM_INCREMENT 0.05
# define INIT_POSX 0.0f
# define INIT_POSY 0.0f
# define MOVE_INCREMENT 0.1

# define BAILOUT_DIST INT_MAX//(1 << 32)

# define NBCOLS 7

//PROCESS DEFINES
# define DRAWN_Y_RANGE (SCN_HEIGHT / NB_DRAWING_PROCS)
# define DRAWN_Y_BYTES (SCN_HEIGHT / NB_DRAWING_PROCS)
//# define DRAWN_LAST_Y_RANGE SCN_HEIGHT - ((NB_DRAWING_PROCS - 1) * DRAWN_Y_RANGE)

# define DRAWN_AREA_NB_PIX (DRAWN_Y_RANGE * SCN_WIDTH)
# define DRAWN_AREA_NB_BYTES (DRAWN_AREA_NB_PIX * sizeof(int))
//# define DRAWN_LAST_AREA_NB_BYTES (DRAWN_LAST_Y_RANGE * SCN_WIDTH)

# ifndef MULTIPROC_RENDERING
#  define MULTIPROC_RENDERING 0
# endif

typedef struct	s_mandelbrot_frame
{
	int	instruction;
	double	zoom;
	double	px;
	double	py;
	int	palette[NBCOLS][3];
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
	SIG_STOP,
	SIG_DRAW
};

// extra mem allocation at end of lines + extra line to comply with xserver buffer formating.
typedef struct	s_shared_mem_mproc_double_buff
{
	int		proc_draw_done[NB_DRAWING_PROCS];
	char	*draw_buff;// 								Current buffer to draw on. points to one of buffers below.
	t_img	buff1;//	Copy of mlx->buff1
	t_img	buff2;//	Copy of mlx->buff2
	int		buff1_data[(SCN_WIDTH + 8) * (SCN_HEIGHT + 1)];
	int		buff2_data[(SCN_WIDTH + 8) * (SCN_HEIGHT + 1)];
}	t_shmem;

// Process pool data held by main process
typedef struct	s_process_pool
{
	int	pool_status;
	int	pids[NB_DRAWING_PROCS];
//	int	status[NB_DRAWING_PROCS]; // 1: live 0: finished/not started, -1: error;
	int	rd_pipes[NB_DRAWING_PROCS];
	int	wr_pipes[NB_DRAWING_PROCS];
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
void	draw_mandelbrot(int *arr, t_frm *frm, int y_start, int y_end);
double	mandelbrot_dist(t_pix *pix, int *iters);
void	frac_move_frame(t_super *super, double deltaX, double deltaY);
void	frac_zoom(t_super *super, double increment);
void	frac_update(t_super *super);
void	frac_update_multiprocessor(t_super *super);

t_frm	*init_base_color_palette(t_frm *frm);

// DRAW POOL FUNCTIONS
int	init_process_pool(t_pool *pool, t_frm *frm);
int	close_process_pool(t_pool *pool, t_frm *frm, char *err_msg);
int	force_close_process_pool(t_pool *pool, char *err_msg);
int	order_pool_draw(t_pool *pool, t_frm *frm, t_mlx *mlx);

void	close_fd_ptr_list(int nb_fds, ...);
#endif
