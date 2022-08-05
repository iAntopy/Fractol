/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:40:32 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/05 19:46:04 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Unified keycode macro definitions for unix (X server) and macos
// Include this header in code to get access.

#ifdef __APPLE__
	#include "keycodes_macos.h"
#elif __unix__
	#include "keycodes_xserv.h"
#endif
