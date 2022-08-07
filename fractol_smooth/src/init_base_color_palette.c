/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_base_color_palette.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 21:13:22 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/06 13:15:42 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_base_color_palette(int *palette)
{
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
//	printf("Corner color in init base palette : r %d, g %d, b %d\n", palette[0][0], palette[0][1], palette[0][2]);
//	printf("Second colot in init base palette : r %d, g %d, b %d\n", palette[1][0], palette[1][1], palette[1][2]);
}
