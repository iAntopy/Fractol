/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:29:32 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/23 13:59:52 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	frac_move_frame(t_frm *frm, double deltaX, double deltaY)
{
	frm->px += deltaX * frm->zoom;
	frm->py += deltaY * frm->zoom;
	frac_update(frm);
}

void	frac_zoom(t_frm *frm, double increment)
{
	frm->zoom *= 1 + increment;
	frac_update(frm);
}
