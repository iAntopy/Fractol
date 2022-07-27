/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:52:11 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/27 15:47:13 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdarg.h>

void	close_fd_ptr_list(int nb_fds, ...)
{
	va_list	ap;
	int	*fd;

	va_start(ap, nb_fds);
	while (nb_fds--)
	{
		fd = va_arg(ap, int *);
		close(*fd);
		*fd = -1;
	}
	va_end(ap);
}
