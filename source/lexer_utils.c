/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:54:53 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/23 08:42:18 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	is_token(char c)
{
	return (c == '\"' || c == '\'' || c == '$' || c == '=' ||
			c == '>' || c == '<' || c == '|' || c == '\n');
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