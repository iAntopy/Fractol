/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:18:06 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/03 23:18:50 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "time.h"


void	frac_update(t_super *super)
{
/*
	printf("Frac update :\n");
	printf("Super multiproc : %d\n", super->multiproc);
	if (super->multiproc)
	{
*/
	printf("Multiproc update\n");
	frac_update_multiprocessor(super);
/*
	}
	else
	{
		printf("Clearing buffer\n");
		printf("super->mlx : %p\n", super->mlx);
		mlx_clear_buffer(super->mlx);
		printf("buffer cleared \n");
		draw_mandelbrot((int *)super->mlx->off_buff->addr, super->frm, 0, SCN_HEIGHT);
		mlx_render_buffer(super->mlx);
	}
*/
	printf("Update DONE\n");
}


void	frac_update_multiprocessor(t_super *sup)
{
	printf("\n\n <<<<<< ----- ENTERING MULTIPROC UPDATE ----- >>>>>>>\n");
	printf("frac update : pre clear mlx->buff_size : %zu\n", sup->mlx->buff_size);
	mlx_clear_buffer(sup->mlx);
	ft_memclear(&sup->shmem->buff1, BUFFER_SIZE * 2);
	printf("buffer cleared\n");
//	if (sup->mlx->off_buff == &sup->mlx->buff2)
	if (sup->shmem->draw_buff == &sup->shmem->buff1)
		sup->shmem->draw_buff = &sup->shmem->buff2;
	else	
		sup->shmem->draw_buff = &sup->shmem->buff1;
	printf("pool ptr : %p\n", sup->pool);
	printf("pool->pids ptr : %p\n", sup->pool->pids);
	printf("pool pids 1 and 2 : %d, %d\n", sup->pool->pids[0], sup->pool->pids[1]);
	order_pool_draw(sup->pool, sup->shmem);
	ft_memcpy(sup->mlx->off_buff->addr, sup->shmem->draw_buff->addr, sup->mlx->buff_size);
	mlx_render_buffer(sup->mlx);
	printf(" <<<<<< ----- MULTIPROC UPDATE COMPLET ----- >>>>>>>\n\n\n");
}

void	give_mandelbrot_coord_rundown(t_pix *pix)
{
	double	dist;
	int	iters;

	dist = mandelbrot_dist(pix, &iters);
	printf("[ mandelbrot distance and value after %d iterations ]\n", iters);
	printf("[ - value :	%f + %fi			]\n", creal(pix->z), cimag(pix->z));
	printf("[ - dist :	%f 				]\n", dist);
}

// Moves frame to mouse position
int	frac_mouse_click(int button, int x, int y, t_super *super)//t_frm *frm)
{
	t_pix	pix;
	t_frm	*frm;

	if (y < 0 || x < 0)
		return (0);
	frm = super->frm;
	printf("Pressed mouse button %d\n", button);
	printf("clicked at screen coord : (%d, %d)\n", x, y);
 	pix.sx = x;
	pix.sy = y;
	convert_pix_to_frame(frm, &pix, 1);
	printf("converted screen coords to : (%f, %f)\n", pix.fx, pix.fy);
	if (button == 1)
		frac_move_frame(super, (pix.fx - frm->px) / frm->zoom, (pix.fy - frm->py) / frm->zoom);
	else if (button == 3)
		give_mandelbrot_coord_rundown(&pix);
	return (0);
}

int	frac_key_switch(int keycode, t_super *super)
{
	printf("SOME KEY PRESSED : %d\n", keycode);
	if (keycode == KC_Enter)//36) 
		frac_update(super);
	else if (keycode == KC_Up)
		frac_move_frame(super, 0, -MOVE_INCREMENT);
	else if (keycode == KC_Down)
		frac_move_frame(super, 0, MOVE_INCREMENT);
	else if (keycode == KC_Left)
		frac_move_frame(super, -MOVE_INCREMENT, 0);
	else if (keycode == KC_Right)
		frac_move_frame(super, MOVE_INCREMENT, 0);
	else if (keycode == KC_PageUp)
		frac_zoom(super, -ZOOM_INCREMENT);
	else if (keycode == KC_PageDown)
		frac_zoom(super, ZOOM_INCREMENT);
	else if (keycode == KC_Home)
		frac_zoom(super, -(ZOOM_INCREMENT * 10));
	else if (keycode == KC_End)
		frac_zoom(super, ZOOM_INCREMENT * 10);
	else if (keycode == KC_Backspace)
		super->multiproc = !super->multiproc;
	else if (keycode == KC_P)
		frac_update_multiprocessor(super);
	return (0);
}

//DEBUG DELETE
void	frac_print_defines(void)
{
	printf("	SCN_WIDTH : %d\n	SCN_HEIGHT  %d\n	SCN_MIDX : %f\n	SCN_MIDY : %f\n", SCN_WIDTH, SCN_HEIGHT, SCN_MIDX, SCN_MIDY);
	printf("	FRM_WIDTH : %f\n	FRM_HEIGHT  %f\n	INIT_ZOOM : %f\n	INIT_POSX : %f\n	INIT_POSY : %f\n", FRM_WIDTH, FRM_HEIGHT, INIT_ZOOM, INIT_POSX, INIT_POSY);
	printf("	ASPECT_RATIO : %f\n", ASP_RATIO);
	printf("	BUFFER_SIZE : %zu\n", BUFFER_SIZE);
}

int	on_close(t_super *super)
{
	int	p_status;
	int	exit_status;

	printf("Attempting to close\n");
	printf("attempting to close MLX\n");
	mlx_close(super->mlx);
	printf("MLX closed successfully\n");
	exit_status = 0;
	if (super->pool)
	{
		printf("attempting to close process pool\n");
		p_status = super->pool->pool_status;
		printf("p_status : %d\n", p_status);
		close_process_pool(super->pool, NULL);
		p_status = super->pool->pool_status;
		if (p_status == STATUS_CLOSED)
			printf("Process pool closed successfully.\n");
		else if (p_status == STATUS_BROKEN)
		{
			printf("process pool broken !\n");
			exit_status = 1;
		}
		else if (p_status == STATUS_RUNNING)
		{
			printf("pool still running. Forcing closure\n");
			usleep(500000);
			force_close_process_pool(super->pool, "pool still running at close. Forcing closure.");
			printf("Forced closure complet.\n");
			exit_status = 2;
		}
	}
	printf("Fractol closure complet and successfull !\n");
	exit(exit_status);
}
/*
static void	set_mlx_buffers_as_shared_memory(t_mlx *mlx, t_shmem *sm)
{
	mlx_img_list_t	*img1;
	mlx_img_list_t	*img2;

	img1 = (mlx_img_list_t *)mlx->screen_buff->img;
	img2 = (mlx_img_list_t *)mlx->off_buff->img;
	free(img1->buffer);
	free(img2->buffer);
	img1->buffer = (char *)sm->buff1_data;
	img2->buffer = (char *)sm->buff2_data;
	mlx->screen_buff->addr = sm->buff1_data;
	mlx->off_buff->addr = sm->buff2_data;
	ft_memcpy(&sm->buff1, &mlx->buff1, sizeof(t_img));
	ft_memcpy(&sm->buff2, &mlx->buff2, sizeof(t_img));

	printf("screen_buff data addr ptr : %p\n", mlx->screen_buff->addr);
}
*/
int	main(void)
{
	t_mlx	mlx;
	t_pool	pool;
	t_super	sup;
	t_frm	*frm;

	sup.shmem = mmap(NULL, sizeof(t_shmem) + sysconf(_SC_PAGE_SIZE) - (sizeof(t_shmem) % sysconf(_SC_PAGE_SIZE)), 
		PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (!sup.shmem)
	{
		close_process_pool(&pool, "Pool initialization failed");
		return (-1);
	}
	printf("sizeof shared mem : %zu\n", sizeof(t_shmem) + (sizeof(t_shmem) % sysconf(_SC_PAGE_SIZE)));
	printf("raw sizeof shmem : %zu\n", sizeof(t_shmem));
	printf("aligning sizeof shmem : %zu, pagesize : %zu\n", sizeof(t_shmem) % sysconf(_SC_PAGE_SIZE), sysconf(_SC_PAGE_SIZE));
	
	frm = &sup.shmem->frm;
	frm->zoom = INIT_ZOOM;
	frm->px = INIT_POSX;
	frm->py = INIT_POSY;
	init_base_color_palette(frm);

	if (init_process_pool(&pool, sup.shmem) < 0 || (pool.pool_status != STATUS_RUNNING))
	{
		close_process_pool(&pool, "Pool initialization failed");
		return (-1);
	}

	mlx_init_double_buff_window(&mlx, SCN_WIDTH, SCN_HEIGHT, "Fractol");
	printf("MLX started\n");

	frac_print_defines();

	printf("mlx->off_buff : %p\n", mlx.off_buff);
	sup.mlx = &mlx;
	sup.frm = frm;
	sup.multiproc = MULTIPROC_RENDERING;
	sup.pool = &pool;
//	set_mlx_buffers_as_shared_memory(&mlx, sup.shmem);
	ft_memcpy(&sup.shmem->buff1, &mlx.buff1, sizeof(t_img));
	ft_memcpy(&sup.shmem->buff2, &mlx.buff2, sizeof(t_img));
	sup.shmem->buff1.addr = sup.shmem->buff1_data;
	sup.shmem->buff2.addr = sup.shmem->buff2_data;

	printf("buff1  line_len, bytes per pixel: %d x %d\n", mlx.buff1.line_len, mlx.buff1.bytes_per_pxl);

	mlx_key_hook(mlx.win, frac_key_switch, &sup);
	mlx_mouse_hook(mlx.win, frac_mouse_click, &sup);
	mlx_hook(mlx.win, ON_DESTROY, 0, on_close, &sup);
	
	printf("shared mem ptr to buff1_data : %p\n", &sup.shmem->buff1_data);
	printf("shared mem ptr to buff2_data : %p\n", &sup.shmem->buff2_data);
	printf("screen_buff->addr ptr : %p\n", mlx.screen_buff->addr);
	printf("off_buff->addr ptr : %p\n", mlx.off_buff->addr);

	printf("setting shmem buff1_data[0] to \'+\' char\n");
	sup.shmem->buff1_data[0] = '+';
	printf("shmem buff1_data[0] after setting : %c\n", sup.shmem->buff1_data[0]);

	printf("mlx buff_size : %zu\n", mlx.buff_size);
	printf("mlx->screen_buff->line_len : %d\n", mlx.screen_buff->line_len);

	mlx_set_bg_color(&mlx, 0x000000ff);
	printf("mlx->screen_buff->addr[0] after set bg color : %d\n", mlx.screen_buff->addr[0]);
	printf("mlx buff_size : %zu\n", mlx.buff_size);

	mlx_render_buffer(&mlx);
	printf("mlx buff_size : %zu\n", mlx.buff_size);
//	mlx_set_bg_color(&mlx, 0x00008000);
//	mlx_render_buffer(&mlx);
//	order_pool_draw(&pool, &frm, &mlx);

	mlx_loop(mlx.conn);

	return (0);
}
