/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_shift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:33:45 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/08 09:09:32 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	frac_shift_julia(t_super *sup, double real, double imag)
{
	sup->frm.cx += real;
	sup->frm.cy += imag;
	frac_update(sup);
	sup->needs_update = 1;
}

void	frac_set_julia_shift(t_super *sup, int x, int y)
{
	double	ratio;

	ratio = (double)4.0f / SCN_HEIGHT;
	sup->frm.cx = (double)(x - sup->frm.scn_midx) * ratio;
	sup->frm.cy = (double)(y - sup->frm.scn_midy) * ratio;
	sup->needs_update = 1;
}
