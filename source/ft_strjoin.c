/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:15:08 by obastug           #+#    #+#             */
/*   Updated: 2025/02/26 13:06:25 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "str.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*final_string;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	final_string = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!final_string)
		return (NULL);
	ft_memcpy(final_string, s1, s1_len);
	final_string[s1_len] = '/';
	ft_memcpy(final_string + s1_len + 1, s2, s2_len);
	final_string[s1_len + s2_len + 1] = '\0';
	return (final_string);
}