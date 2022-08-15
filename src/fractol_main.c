/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:18:06 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/12 16:18:41 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "time.h"

int	on_close(t_super *super)
{
	printf("Attempting to close\n");
	printf("attempting to close MLX\n");
	mlx_close(super->mlx);
	printf("MLX closed successfully\n");
	printf("Fractol closure complet and successfull !\n");
	exit(0);
}

void	frac_update(t_super *sup)
{
	printf("Frac update :\n");
	printf("Clearing buffer\n");
	printf("super->mlx : %p\n", sup->mlx);
	mlx_clear_buffer(sup->mlx);
	printf("buffer cleared \n");
	draw_mandelbrot(sup->mlx->off_buff, sup->frm);
	mlx_render_buffer(sup->mlx);
	printf("Update DONE\n");
}

void	give_mandelbrot_coord_rundown(t_pix *pix, t_frm *frm)
{
	frm->dist_func(pix);
//	mandelbrot_dist(pix, pix->z);
	printf("[ mandelbrot distance and value after %d iterations ]\n", pix->iters);
	printf("[ - value :	%f + %fi			]\n", creal(pix->z), cimag(pix->z));
	printf("[ - dist :	%f 				]\n", pix->dist);
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
/*
int	invalid_input_arg_procedure(char *arg)
{
		fperror(RED_BC"Invalid argument from display mode : %s\n"WHITE_C, arg);
		display_help();
		return (-1);
}

int	frac_parse_args(t_super *sup, int argc, char **argv)
{
	char	*arg;
	char	*mode;
	char	*p;

	if (argc == 1)
	{
		display_help();
		return (0);
	}
	mode = argv[1];
	if (ft_strcmp(ft_tolower(argv[1]), "mandelbrot") == 0)
		sup->frm->dist_func = mandelbrot_dist;
	else if (ft_strcmp(ft_tolower(argv[1]), "julia") == 0)
		sup->frm->dist_func = julia_dist;
	else
		return (invalid_input_arg_procedure(argv[1]));
	if (argc > 2)
	{
		arg = argv[2];
		p = ft_strchr(arg, '(');
		if (!p)
			return (invalid_input_arg_procedure(argv[2]));
		sup->frm->px = ft_atoi(p + 1);
		p = ft_strchr(p + 1, ',');
		if (!p)
			return (invalid_input_arg_procedure(argv[2]));
		sup->frm->py = ft_atoi(p + 1);
		if (!ft_strchr(p + 1, ')'))
			return (invalid_input_arg_procedure(argv[2]));
	}
	return (1);
}
*/
int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_frm	frm;
	t_super	super_struct;

	(void)argc;
	(void)argv;
	init_frame(&frm);
	init_base_color_palette(&frm.pal, PALETTE_MIAMI);
	
	mlx_init_double_buff_window(&mlx, SCN_WIDTH, SCN_HEIGHT, "Fractol");
	printf("MLX started\n");
//	frac_print_defines();

	printf("mlx->screen_buff : %p\n", mlx.screen_buff);
	printf("mlx->off_buff : %p\n", mlx.off_buff);
	super_struct.mlx = &mlx;
	super_struct.frm = &frm;
	init_mouse_data(&super_struct);

	printf("buff1  line_len, bytes per pixel: %d x %d\n", mlx.buff1.line_len, mlx.buff1.bytes_per_pxl);

	mlx_key_hook(mlx.win, frac_key_switch, &super_struct);
	mlx_hook(mlx.win, ON_DESTROY, 0, on_close, &super_struct);
//	mlx_mouse_hook(mlx.win, on_mouse_wheel, &super_struct);
	mlx_hook(mlx.win, ON_MOUSEUP, (1L << 3), on_mouse_release, &super_struct);
	mlx_hook(mlx.win, ON_MOUSEDOWN, (1L << 2), on_mouse_press, &super_struct);
	mlx_hook(mlx.win, ON_MOUSEMOVE, (1L << 6), on_mouse_drag, &super_struct);
	
//	mlx_set_bg_color(&mlx, 0x000000ff);
//	mlx_render_buffer(&mlx);

	frac_update(&super_struct);
	mlx_loop(mlx.conn);
	return (0);
}
