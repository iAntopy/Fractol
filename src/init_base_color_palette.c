/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_base_color_palette.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 21:13:22 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/07 02:49:39 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_palette_miami(t_pal *pal)
{
	pal->nb_cols = 7;
	pal->pal_code = PALETTE_MIAMI;
	pal->palette[0][0] = 0x00;
	pal->palette[0][1] = 0x00;
	pal->palette[0][2] = 0x00;
	pal->palette[1][0] = 0x21;
	pal->palette[1][1] = 0x61;
	pal->palette[1][2] = 0xff;
	pal->palette[2][0] = 0xdb;
	pal->palette[2][1] = 0x21;
	pal->palette[2][2] = 0xff;
	pal->palette[3][0] = 0xff;
	pal->palette[3][1] = 0x21;
	pal->palette[3][2] = 0x24;
	pal->palette[4][0] = 0xff;
	pal->palette[4][1] = 0xe3;
	pal->palette[4][2] = 0x21;
	pal->palette[5][0] = 0xb2;
	pal->palette[5][1] = 0xff;
	pal->palette[5][2] = 0x21;
	pal->palette[6][0] = 0xff;
	pal->palette[6][1] = 0xff;
	pal->palette[6][2] = 0xff;
	printf("Miami color palette engaged !\n");
}

void	init_palette_monochrome(t_pal *pal)
{
	pal->nb_cols = 2;
	pal->pal_code = PALETTE_MONOCHROME;
	pal->palette[0][0] = 0x00;
	pal->palette[0][1] = 0x00;
	pal->palette[0][2] = 0x00;
	pal->palette[1][0] = 0xff;
	pal->palette[1][1] = 0xff;
	pal->palette[1][2] = 0xff;
	printf("Monochrome color palette engaged !\n");
}

void	init_palette_orange(t_pal *pal)
{
	pal->nb_cols = 4;
	pal->pal_code = PALETTE_ORANGE;
	pal->palette[0][0] = 0x00;
	pal->palette[0][1] = 0x00;
	pal->palette[0][2] = 0x00;
	pal->palette[1][0] = 0xd9;
	pal->palette[1][1] = 0x25;
	pal->palette[1][2] = 0x00;
	pal->palette[2][0] = 0xff;
	pal->palette[2][1] = 0x90;
	pal->palette[2][2] = 0x25;
	pal->palette[3][0] = 0xff;
	pal->palette[3][1] = 0xff;
	pal->palette[3][2] = 0xff;
	printf("Orange color palette engaged !\n");
}

void	init_palette_green(t_pal *pal)
{
	pal->nb_cols = 4;
	pal->pal_code = PALETTE_GREEN;
	pal->palette[0][0] = 0x00;
	pal->palette[0][1] = 0x00;
	pal->palette[0][2] = 0x00;
	pal->palette[1][0] = 0x15;
	pal->palette[1][1] = 0xdb;
	pal->palette[1][2] = 0x15;
	pal->palette[2][0] = 0x2e;
	pal->palette[2][1] = 0xff;
	pal->palette[2][2] = 0x6d;
	pal->palette[3][0] = 0xff;
	pal->palette[3][1] = 0xff;
	pal->palette[3][2] = 0xff;
	printf("Green color palette engaged !\n");
}

void	init_base_color_palette(t_pal *pal, int pal_code)
{
	if (pal_code == PALETTE_MIAMI)
		init_palette_miami(pal);
	else if (pal_code == PALETTE_MONOCHROME)
		init_palette_monochrome(pal);
	else if (pal_code == PALETTE_ORANGE)
		init_palette_orange(pal);
	else if (pal_code == PALETTE_GREEN)
		init_palette_green(pal);
	else
		fperror("Invalid palette code");
}


