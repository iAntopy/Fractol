/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:40:32 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/20 07:35:54 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Unified keycode macro definitions for unix (X server) and macos
// Include this header in code to get access.
#ifndef KEYCODES_H
# define KEYCODES_H

# ifdef __APPLE__
#  include "keycodes_macos.h"
# elif __unix__
#  include "keycodes_xserv.h"
# endif
#endif
