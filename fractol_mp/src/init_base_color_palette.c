/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_base_color_palette.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 21:13:22 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/06 13:38:05 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_palette_miami(t_pal *pal)
{
	int	palette[10][3];

	palette = pal->palette;
	pal->nb_cols = 7;
	palette[0][0] = 0x00;
	palette[0][1] = 0x00;
	palette[0][2] = 0x00;
	palette[1][0] = 0x21;
	palette[1][1] = 0x61;
	palette[1][2] = 0xff;
	palette[2][0] = 0xdb;
	palette[2][1] = 0x21;
	palette[2][2] = 0xff;
	palette[3][0] = 0xff;
	palette[3][1] = 0x21;
	palette[3][2] = 0x24;
	palette[4][0] = 0xff;
	palette[4][1] = 0xe3;
	palette[4][2] = 0x21;
	palette[5][0] = 0xb2;
	palette[5][1] = 0xff;
	palette[5][2] = 0x21;
	palette[6][0] = 0xff;
	palette[6][1] = 0xff;
	palette[6][2] = 0xff;
}

void	init_palette_monochrome(t_pal *pal)
{
	int	palette[10][3];

	palette = pal->palette;
	pal->nb_cols = 2;
	palette[0][0] = 0x00;
	palette[0][1] = 0x00;
	palette[0][2] = 0x00;
	palette[1][0] = 0xff;
	palette[1][1] = 0xff;
	palette[1][2] = 0xff;
}

void	init_base_color_palette(t_pal *pal, int pal_code)
{
	if (pal_code == PALETTE_MIAMI)
		init_palette_miami(palette);
	else if (pal_code == PALETTE_MONOCHROME)
		init_palette_monochrome(palette);
	else
		ft_perror("Invalid palette code");
}


