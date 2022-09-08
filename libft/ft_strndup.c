/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:53:03 by iamongeo          #+#    #+#             */
/*   Updated: 2022/03/28 15:53:06 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	char	*dup;
	char	*d;
	size_t	str_len;

	str_len = ft_strlen(str);
	if (n < str_len)
		str_len = n;
	dup = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!dup)
		return (NULL);
	d = dup;
	while (str_len--)
		*(d++) = *(str++);
	*d = '\0';
	return (dup);
}

/*
int	main(void)
{
	char	*dup;
	char	src[] = "Kawaboonga !";

	dup = ft_strndup(src + 1, 4);
	ft_putstr(dup);
	return (0);
}
*/
