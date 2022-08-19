/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:18:06 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/18 23:37:30 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "time.h"

int	on_close(t_super *super)
{
	mlx_close(super->mlx);
	exit(0);
}

void	frac_update(t_super *sup)
{
	mlx_clear_buffer(sup->mlx);
	draw_mandelbrot(sup->mlx->off_buff, sup->frm);
	mlx_render_buffer(sup->mlx);
}

void	init_frame(t_frm *frm)
{
	frm->zoom = INIT_ZOOM;
	frm->px = INIT_POSX;
	frm->py = INIT_POSY;
	frm->ang = INIT_ANGLE;
	frm->cx = INIT_CREAL;
	frm->cy = INIT_CIMAG;
	frm->dist_func = mandelbrot_dist;
}

void	init_event_hooks(t_super *sup)
{
	mlx_key_hook(sup->mlx->win, frac_key_switch, sup);
	mlx_hook(sup->mlx->win, ON_DESTROY, 0, on_close, sup);
	mlx_hook(sup->mlx->win, ON_MOUSEUP, (1L << 3), on_mouse_release, sup);
	mlx_hook(sup->mlx->win, ON_MOUSEDOWN, (1L << 2), on_mouse_press, sup);
	mlx_hook(sup->mlx->win, ON_MOUSEMOVE, (1L << 6), on_mouse_drag, sup);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_frm	frm;
	t_super	sup;

	init_frame(&frm);
	if (!parse_inputs(&frm, argc, argv))
		return (1);
	mlx_init_double_buff_window(&mlx, SCN_WIDTH, SCN_HEIGHT, "Fractol");
	sup.mlx = &mlx;
	sup.frm = &frm;
	init_mouse_data(&sup);
	init_event_hooks(&sup);
	frac_update(&sup);
	mlx_loop(mlx.conn);
	return (0);
}
