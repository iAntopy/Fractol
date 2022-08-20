/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 06:33:56 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/20 07:17:26 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	frac_update(t_super *sup)
{
	t_shmem	*sm;
	t_img	*buff;

	sm = sup->shmem;
	if (sm->draw_buff == &sm->buff1)
		sm->draw_buff = &sm->buff2;
	else
		sm->draw_buff = &sm->buff1;
	buff = sm->draw_buff;
	ft_memclear(buff->addr, sup->mlx->buff_size);
	if (order_pool_draw(sup->pool, sm) < 0)
	{
		on_close(sup);
		return ;
	}
	ft_memcpy(sup->mlx->off_buff->addr, buff->addr, sup->mlx->buff_size);
	mlx_render_buffer(sup->mlx);
}

static void	calc_tgt_to_scn_frm_delta(double dfrm[6], t_frm *tfrm, t_frm *sfrm)
{
	dfrm[0] = tfrm->px - sfrm->px;
	dfrm[1] = tfrm->py - sfrm->py;
	dfrm[2] = tfrm->zoom - sfrm->zoom;
	dfrm[3] = tfrm->ang - sfrm->ang;
	dfrm[4] = tfrm->cx - sfrm->cx;
	dfrm[5] = tfrm->cy - sfrm->cy;
}

static void	update_frame_state(double dfrm[6], t_frm *sfrm)
{
	sfrm->px += dfrm[0] / SMOOTHNESS;
	sfrm->py += dfrm[1] / SMOOTHNESS;
	sfrm->zoom += dfrm[2] / SMOOTHNESS;
	sfrm->ang += dfrm[3] / SMOOTHNESS;
	sfrm->cx += dfrm[4] / SMOOTHNESS;
	sfrm->cy += dfrm[5] / SMOOTHNESS;
}

static int	frame_state_within_threashold(double dfrm[6], double zoom)
{
	return (((fabs(dfrm[0]) + fabs(dfrm[1])) / zoom < MV_THLD)
		&& fabs(dfrm[2]) / zoom < ZM_THLD
		&& fabs(dfrm[3]) < RT_THLD
		&& (fabs(dfrm[4]) + fabs(dfrm[5])) < JL_THLD);
}

int	on_update(t_super *sup)
{
	static ssize_t	cumul_time;
	double			dfrm[6];

	cumul_time += ft_deltatime_usec();
	if ((!sup->needs_update) || (cumul_time < FRAME_USEC))
		return (0);
	calc_tgt_to_scn_frm_delta(dfrm, &sup->frm, &sup->shmem->sfrm);
	if (frame_state_within_threashold(dfrm, sup->shmem->sfrm.zoom))
		sup->needs_update = 0;
	else
	{
		update_frame_state(dfrm, &sup->shmem->sfrm);
		frac_update(sup);
		cumul_time = 0;
	}
	return (0);
}
