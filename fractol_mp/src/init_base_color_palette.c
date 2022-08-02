/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_base_color_palette.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 21:13:22 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/25 00:32:34 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_frm	*init_base_color_palette(t_frm *frm)
{
//	frm->palette[0] = 0x002161ff;
//	frm->palette[1] = 0x00db21ff;
///	frm->palette[2] = 0x00ff2124;
//	frm->palette[3] = 0x00ffe321;
//	frm->palette[4] = 0x00b2ff21;
//	frm->palette[5] = 0x00ffffff;
	frm->palette[0][0] = 0x00;
	frm->palette[0][1] = 0x00;
	frm->palette[0][2] = 0x00;
	
	frm->palette[1][0] = 0x21;
	frm->palette[1][1] = 0x61;
	frm->palette[1][2] = 0xff;

	frm->palette[2][0] = 0xdb;
	frm->palette[2][1] = 0x21;
	frm->palette[2][2] = 0xff;

	frm->palette[3][0] = 0xff;
	frm->palette[3][1] = 0x21;
	frm->palette[3][2] = 0x24;

	frm->palette[4][0] = 0xff;
	frm->palette[4][1] = 0xe3;
	frm->palette[4][2] = 0x21;

	frm->palette[5][0] = 0xb2;
	frm->palette[5][1] = 0xff;
	frm->palette[5][2] = 0x21;

	frm->palette[6][0] = 0xff;
	frm->palette[6][1] = 0xff;
	frm->palette[6][2] = 0xff;
	printf("Corner color in init base palette : r %d, g %d, b %d\n", frm->palette[0][0], frm->palette[0][1], frm->palette[0][2]);
	printf("Second colot in init base palette : r %d, g %d, b %d\n", frm->palette[1][0], frm->palette[1][1], frm->palette[1][2]);
	return (frm);
}
