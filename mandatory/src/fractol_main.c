/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:18:06 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/08 09:45:10 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	on_close(t_super *sup, int has_failed, int exit_code)
{
	mlx_close(sup->mlx);
	if (has_failed == EXIT_WERROR)
		exit(exit_code);
	exit(EXIT_SUCCESS);
}

static void	init_event_hooks(t_super *sup)
{
	init_mouse_data(sup);
	mlx_key_hook(sup->mlx->win, frac_key_switch, sup);
	mlx_hook(sup->mlx->win, ON_DESTROY, 0, on_close, sup);
	mlx_hook(sup->mlx->win, ON_MOUSEUP, (1L << 3), on_mouse_release, sup);
	mlx_hook(sup->mlx->win, ON_MOUSEDOWN, (1L << 2), on_mouse_press, sup);
	mlx_hook(sup->mlx->win, ON_MOUSEMOVE, (1L << 6), on_mouse_drag, sup);
}

t_frm	*init_frame(t_frm *frm)
{
	frm->scn_midx = SCN_WIDTH / 2;
	frm->scn_midy = SCN_HEIGHT / 2;
	frm->zoom = 4.0f / SCN_HEIGHT;
	frm->px = INIT_POSX;
	frm->py = INIT_POSY;
	frm->cx = INIT_CREAL;
	frm->cy = INIT_CIMAG;
	frm->ang = INIT_ANGLE;
	frm->cos_a = cos(frm->ang);
	frm->sin_a = sin(frm->ang);
	frm->dist_func = mandelbrot_dist;
	return (frm);
}

t_frm	*reset_frame(t_frm *frm)
{
	frm->zoom = 4.0f / SCN_HEIGHT;
	frm->px = INIT_POSX;
	frm->py = INIT_POSY;
	frm->ang = INIT_ANGLE;
	return (frm);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_super	sup;

	init_frame(&sup.frm);
	if (!parse_inputs(&sup.frm, argc, argv))
		return (EXIT_PARSING_FAILED);
	mlx_init_double_buff_window(&mlx, SCN_WIDTH, SCN_HEIGHT, "Fractol");
	sup.mlx = &mlx;
	init_event_hooks(&sup);
	frac_update(&sup);
	mlx_loop(mlx.conn);
	return (EXIT_SUCCESS);
}
