/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:17:39 by iamongeo          #+#    #+#             */
/*   Updated: 2023/05/02 02:44:40 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OMNI_MLX_H
# define OMNI_MLX_H

# ifdef __linux__
#  include "mlx_linux.h"
# elif __unix__
#  include "mlx_linux.h"
# elif __APPLE__
#  include "mlx_macos.h"
# endif

#endif
