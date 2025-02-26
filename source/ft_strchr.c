/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:00:53 by obastug           #+#    #+#             */
/*   Updated: 2025/02/26 15:01:17 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	register size_t	i;
	unsigned char	*tmp_s;
	unsigned char	tmp_c;

	tmp_s = (unsigned char *)s;
	tmp_c = (unsigned char)c;
	i = -1;
	while (++i < n)
	{
		if (tmp_s[i] == tmp_c)
			return (tmp_s + i);
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	return (ft_memchr(s, c, ft_strlen(s) + 1));
}
