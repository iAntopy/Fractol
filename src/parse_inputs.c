/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:18:45 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/09 01:25:46 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_core.h"

static int	display_list_commands(void)
{
	ft_printf("\nKeybindings :\n\n");
	ft_printf("\t\t- [w,a,s,d] | numpad [8,4,5,6] : up, left, down, right\n");
	ft_printf("\t\t- [PageUp, PageDn] | numpad [+,-] : zoom in/out\n");
	ft_printf("\t\t- [q,e] | numpad [7,9] : rotate anti-clockwise/clockwise\n");
	ft_printf("\t\t- Dir. arrows : change init C param for julia set\n");
	ft_printf("\t\t- Escape : close window\n");
	ft_printf("\t\t- Enter : Force update window\n");
	ft_printf("\t\t- Delete : Reset frame to init state\n");
	ft_printf("\t\t- Backspace : Switch fractal being displayed\n");
	ft_printf("\t\t- c : Switch color palette\n");
	ft_printf("\nMouse commands :\n\n");
	ft_printf("\t\t- Mouse click : set focus position\n");
	ft_printf("\t\t- Mouse wheel : zoom in/out directional\n");
	ft_printf("\t\t- Mouse left drag : slide frame position\n");
	ft_printf("\t\t- Mouse wheel button drag : slide C param for julia set\n");
	return (0);
}

static int	display_help(void)
{
	ft_printf("At least one parameter must be provided to run.\n\n");
	ft_printf("\t 1st param is one of the following fractals to display :\n");
	ft_printf("\t\t- mandelbrot\n\t\t- mandelbrot julia\n");
	ft_printf("\t\t- burning ship\n\t\t- burning ship julia\n");
	ft_printf("\t\t- celtic\n\t\t- celtic julia\n");
	ft_printf("\t\t- crown\n\t\t- crown julia\n");
	ft_printf("\t\t- temple\n\t\t- temple julia\n");
	ft_printf("\t\t- 5th order\n\t\t- 5th order julia\n");
	ft_printf("\n\t 2nd param is one of the following color palettes :\n\n");
	ft_printf("\t\t- rainbow\n");
	ft_printf("\t\t- monochrome\n");
	ft_printf("\t\t- red\n");
	ft_printf("\t\t- green\n");
	return (display_list_commands());
}

static int	parse_arg2(t_frm *frm, char *arg)
{
	ft_strlower(arg);
	if (ft_strcmp(arg, "rainbow") == 0)
		init_base_color_palette(&frm->pal, PALETTE_MIAMI);
	else if (ft_strcmp(arg, "monochrome") == 0)
		init_base_color_palette(&frm->pal, PALETTE_MONOCHROME);
	else if (ft_strcmp(arg, "red") == 0)
		init_base_color_palette(&frm->pal, PALETTE_ORANGE);
	else if (ft_strcmp(arg, "green") == 0)
		init_base_color_palette(&frm->pal, PALETTE_GREEN);
	else
		return (display_help());
	return (1);
}

static void	parse_arg1(t_frm *frm, char *arg)
{
	if (ft_strcmp(arg, "mandelbrot") == 0)
		frm->dist_func = mandelbrot_dist;
	else if (ft_strcmp(arg, "mandelbrot julia") == 0)
		frm->dist_func = julia_dist;
	else if (ft_strcmp(arg, "burning ship") == 0)
		frm->dist_func = burning_ship_dist;
	else if (ft_strcmp(arg, "burning ship julia") == 0)
		frm->dist_func = burning_ship_julia_dist;
	else if (ft_strcmp(arg, "celtic") == 0)
		frm->dist_func = celtic_dist;
	else if (ft_strcmp(arg, "celtic julia") == 0)
		frm->dist_func = celtic_julia_dist;
	else if (ft_strcmp(arg, "crown") == 0)
		frm->dist_func = crown_dist;
	else if (ft_strcmp(arg, "crown julia") == 0)
		frm->dist_func = crown_julia_dist;
	else if (ft_strcmp(arg, "temple") == 0)
		frm->dist_func = temple_dist;
	else if (ft_strcmp(arg, "temple julia") == 0)
		frm->dist_func = temple_julia_dist;
	else if (ft_strcmp(arg, "5th order") == 0)
		frm->dist_func = mandelbrot_5th_order_dist;
	else if (ft_strcmp(arg, "5th order julia") == 0)
		frm->dist_func = julia_5th_order_dist;
}

int	parse_inputs(t_frm *frm, int argc, char **argv)
{
	if (argc == 1)
		return (display_help());
	ft_strlower(argv[1]);
	frm->dist_func = NULL;
	parse_arg1(frm, argv[1]);
	if (!frm->dist_func)
		return (display_help());
	if (argc > 2)
	{
		if (!parse_arg2(frm, argv[2]))
			return (0);
	}
	else
		init_base_color_palette(&frm->pal, PALETTE_MIAMI);
	return (1);
}
