/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:17:39 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/18 17:22:21 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

# ifdef __linux__
#  include "mlx_linux.h"
# elif __APPLE__
#  include "mlx_macos.h"
# endif

#endif
