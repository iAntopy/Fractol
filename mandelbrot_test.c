/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:05:11 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/22 20:36:15 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>

#define SCN_WIDTH 1000
#define SCN_HEIGHT 1000
#define SCN_MIDX (SCN_WIDTH / 2)
#define SCN_MIDY (SCN_HEIGHT / 2)
#define FRM_WIDTH 4.0f
#define FRM_HEIGHT 4.0f
#define MAX_ITER 100
#define INIT_ZOOM 1
#define ZOOM_INCREMENT 0.01
#define INIT_POSX 0
#define INIT_POSY 0
#define MOVE_INCREMENT 0.1

typedef struct	s_frame
{
	double	zoom;
	double	px;
	double	py;
}	t_frame;

typedef struct	s_pixel
{
	double	x;
	double	y;
}	t_pix;


// Returns dist after 100 iterations
double	mandelbrot_dist(t_pix *pix)
{
	int				i;
	double complex	z;
	double complex	c;

	z = 0;
	c = pix->x + (pix->y * I);
	i = -1;
	while (++i < MAX_ITER)
	{
		z = (z * z) + c;
		if (fabs(creal(z)) > 1000)
			break ;
	}
	pix->z = z;
	return (hypot(creal(z), cimag(z)));
}

void	convert_pix_to_frame(t_frame *frm, t_pix *pix)
{
	pix->x = frm->zoom * FRM_WIDTH * ((pix->x - SCN_MIDX) / SCN_WIDTH) + frm->px;
	pix->y = frm->zoom * FRM_HEIGHT * ((pix->y - SCN_MIDY) / SCN_HEIGHT) + frm->py;
}

void	draw_mandelbrot(t_frame *frm)
{
	t_pix	pix;
	int		x;
	int		y;
	double	dist;

	y = -1;
	while (++y < SCN_HEIGHT)
	{
		x = -1;
		while (++x < SCN_WIDTH)
		{
			pix.x = x;
			pix.y = y;
			convert_pix_to_frame(frm, &pix);
			dist = mandelbrot_dist(&pix);
			if (dist > 2)
				draw_pixel(x, y, dist);
	}
}

t_frame	*set_frame(t_frame *frm, double zoom, double x_offset, double y_offset)
{
	frm->zoom = zoom;
	frm->px = x_offset;
	frm->py = y_offset;
	return (frm);
}

//ZOOM IN EVENT
void	scroll_up_hook(int x, int y, t_frame *frm)
{
	frm->zoom *= 1 - ZOOM_INCREMENT;
	redraw();
}

//ZOOM OUT EVENT
void	scroll_out_hook(int x, int y, t_frame *frm)
{
	frm->zoom *= 1 + ZOOM_INCREMENT;
	redraw();
}

//DIRECTIONAL ZOOM IN EVENT
void	scroll_up_directional_hook(int x, int y, t_frame *frm)
{
	frm->px += MOVE_INCREMENT * FRM_WIDTH * ((x - SCN_MIDX) / SCN_WIDTH);
	frm->py += MOVE_INCREMENT * FRM_HEIGHT * ((y - SCN_MIDY) / SCN_HEIGHT);
	frm->zoom *= 1 - ZOOM_INCREMENT;
	redraw();
}

//DIRECTIONAL ZOOM OUT EVENT
void	scroll_out_directional_hook(int x, int y, t_frame *frm)
{
	frm->px += MOVE_INCREMENT * FRM_WIDTH * ((x - SCN_MIDX) / SCN_WIDTH);
	frm->py += MOVE_INCREMENT * FRM_HEIGHT * ((y - SCN_MIDY) / SCN_HEIGHT);
	frm->zoom *= 1 + ZOOM_INCREMENT;
	redraw();
}

int	main(void)
{
	t_frame	frm;

	frm = init_frame(&frm, INIT_ZOOM, INIT_POSX, INIT__POSY);
	draw_mandelbrot(&frm);
	return (0);
}
