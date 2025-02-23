/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 05:04:51 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/23 06:00:16 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

int		is_token(char c);
char	*ft_strndup(const char	*str, int len);
int		ft_strlen(const char *str);
char	*expand_dquote(char *token_value);


char	*expand_dollar(char *token_value) // ADD ONLY $? NOT $_ OR $$ add struct for it
{
	char	*ret;
	char	*trim;
	int		i;

	i = 0;
	if (!token_value[i + 1] || token_value[i + 1] == ' ' || is_token(token_value[i+1]))
		return (ft_strndup("$", 0));
	while (token_value[i+1] && token_value[i+1] != ' ' && !is_token(token_value[i+1]))
		i++;
	trim = ft_strndup(token_value + 1, i);
	if (!trim)
		return (NULL);
	ret = getenv(trim);
	free(trim);
	if (!ret)
		return (ft_strndup("", 0));
	return (ft_strndup(ret, 0));
}

static char	*expand_quote(char *token_value)
{
	char	*ret;
	int		len;
	
	len = ft_strlen(token_value);
	ret = malloc(len - 1);
	if (!ret)
		return (NULL);
	ft_strndup(token_value + 1, len - 2);
	ret[len - 2] = '\0';
	return (ret);
}

void	expander(t_token *tokens)
{
	char	*expanded;
	int		i;

	i = -1;
	while ((tokens[++i].value))
	{
		if (*(tokens[i].value) == '\"') // "abc" -> abc && if arg=smthng "abc $arg" -> abc smthng
			expanded = expand_dquote(tokens[i].value);
		else if (*(tokens[i].value) == '\'') // 'abc' -> abc
			expanded = expand_quote(tokens[i].value);
		else if (*(tokens[i].value) == '$') // if arg=something $arg -> someting
			expanded = expand_dollar(tokens[i].value);
		else
			continue;
		if (!expanded)
			return ;
		free(tokens[i].value);
		tokens[i].value = expanded;
	}
}
