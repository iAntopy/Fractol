/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:29:32 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/25 22:19:40 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	frac_move_frame(t_super *super, double deltaX, double deltaY)
{
	super->frm->px += deltaX * super->frm->zoom;
	super->frm->py += deltaY * super->frm->zoom;
	if (super->multiproc)
		frac_update_multiprocessor(super);
	else
		frac_update(super);
}

void	frac_zoom(t_super *super, double increment)
{
	super->frm->zoom *= 1 + increment;
	if (super->multiproc)
		frac_update_multiprocessor(super);
	else
		frac_update(super);
}
