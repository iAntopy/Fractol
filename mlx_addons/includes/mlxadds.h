/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxadds.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:32:17 by iamongeo          #+#    #+#             */
/*   Updated: 2023/05/01 15:48:34 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXADDS_H
# define MLXADDS_H

# include <stdlib.h>

# include "mlx.h"
# include "libft.h"

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

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bytes_per_pxl;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mlx_data
{
	void	*conn;
	void	*win;
	int		width;
	int		height;
	size_t	nb_pix;
	size_t	buff_size;
	t_img	*scn_buff;
	t_img	*off_buff;
	t_img	buff1;
	t_img	buff2;
}	t_mlx;

t_mlx	*mlx_init_double_buff_window(t_mlx *mlx, int w, int h, char *title);
int		mlx_swap_buffers(t_mlx *mlx);
int	*mlx_index_buffer(t_img *buff, int x, int y);
void	mlx_buff_put_pixel(t_img *img, int x, int y, int col);
void	mlx_draw_line(t_mlx *mlx, int start[2], int end[2], int col);
void	mlx_clear_buffer(t_mlx *mlx);
void	mlx_set_bg_color(t_mlx *mlx, int col);
void	mlx_fill_color_region(t_mlx *mlx, int start[2], int end[2], int col);
int		mlx_render_buffer(t_mlx *mlx);
void	mlx_close(t_mlx *mlx);
void	mlx_get_info(t_mlx *mlx);

#endif
