/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:18:06 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/22 23:36:24 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "time.h"

int	frac_update(int keycode, t_frm *frm)
{
	printf("SOME KEY PRESSED : %d\n", keycode);
	if (keycode == KC_Enter)//36) 
	{
		printf("Pressed ENTER\n");
		draw_mandelbrot(frm->mlx, frm);
		printf("mandelbrot drawn ... presumebly\n");
		mlx_render_buffer(frm->mlx);
		printf("mandelbrot rendered ... presumebly\n");
	}
	return (0);
}

int	main(void)
{
	t_mlx	mlx;
	t_frm	frm;

	frm.zoom = INIT_ZOOM;
	frm.px = INIT_POSX;
	frm.py = INIT_POSY;

	mlx_init_double_buff_window(&mlx, SCN_WIDTH, SCN_HEIGHT, "Fractol");
	
	frm.mlx = &mlx;	
	frm.zoom = INIT_ZOOM;
	frm.px = INIT_POSX;
	frm.py = INIT_POSY;

	mlx_key_hook(mlx.win, frac_update, &frm);

	mlx_loop(&mlx);

	return (0);
}
