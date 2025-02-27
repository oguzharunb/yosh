/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 23:04:04 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/27 20:03:46 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *str)
{
	int	len;
	int	i;
	char	*ret;

	if (!str)
	{
		ret = malloc(sizeof(char) * 1);
		ret[0] = '\0';
		return (ret);
	}
	len = 0;
	while (str[len])
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if(ret == NULL)
		return (NULL);
	i = -1;
	while(++i < len)
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}
