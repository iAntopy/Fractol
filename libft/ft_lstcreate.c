/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcreate_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:47:39 by iamongeo          #+#    #+#             */
/*   Updated: 2022/03/28 15:48:24 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcreate(void *content, size_t size)
{
	void	*data;
	t_list	*lst;

	data = malloc(size);
	ft_memcpy(data, content, size);
	lst = ft_lstnew(data);
	return (lst);
}
