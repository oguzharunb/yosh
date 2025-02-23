/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:54:53 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/23 04:57:10 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	is_token(char c)
{
	return (c == '\"' || c == '\'' || c == '$' || c == '=' ||
			c == '>' || c == '<' || c == '|' || c == '\n');
}

int	strcomp(char *str1, char *str2)
{
	if (!str1)
		return (0);
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (0);
		str1++;
		str2++;
	}
	if ((!(*str2) && *str1) || (!(*str1) && *str2))
		return (0);
	return (1);
}
char	*token_dup(const char *s, int size)
{
	char	*dup;
	int		i;

	dup = malloc(sizeof(char) * size + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}