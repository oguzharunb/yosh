/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:58:18 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/23 06:01:33 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(const char *str)
{
	const char	*p;
	
	p = str;
	while (*p)
		p++;
	return (p - str);
}

char	*ft_strndup(const char	*str, int len)
{
	int i;
	char	*ret;

	if (!len)
		len = ft_strlen(str);
	ret = malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i = -1;
	while(++i < len)
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}
