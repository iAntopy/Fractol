/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxadds.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:32:17 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/22 23:11:12 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXADDS_H
# define MLXADDS_H

# include <stdlib.h>

# include "mlx.h"

enum	e_event_codes
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17

};

typedef struct	s_img_data
{
	void	*img;
	char	*addr;
	int	bytes_per_pxl;	//Don't forget to divide bits_per_pixel by 8.
	int	line_len;
	int	endian;	
}	t_img;

typedef struct	s_mlx_data
{
	void	*mlx;
	void	*win;
	int	width;
	int	height;
	t_img	*screen_buff;
	t_img	*off_buff;
	t_img	buff1;
	t_img	buff2;
}	t_mlx;

t_mlx	*mlx_init_double_buff_window(t_mlx *mlx, int width, int height, char *title);
int	mlx_swap_buffers(t_mlx *mlx);
void	mlx_buff_put_pixel(t_img *img, int x, int y, int col);
void	mlx_draw_line(t_mlx *mlx, int start[2], int end[2], int col);
void	mlx_clear_buffer(t_mlx *mlx); //Clears the off screen buffer by setting its data to 0.
void	mlx_set_bg_color(t_mlx *mlx, int col);
void	mlx_render_buffer(t_mlx *mlx);

#endif
