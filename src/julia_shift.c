/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_shift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:33:45 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/07 01:08:50 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	frac_shift_julia(t_super *sup, double real, double imag)
{
	sup->frm->cx += real;
	sup->frm->cy += imag;
	frac_update(sup);
}
