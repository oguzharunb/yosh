/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 05:04:51 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/23 04:15:23 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	while (n--)
	{
		*d++ = *s++;
	}
	return (dst);
}
static char	*ft_strdup(const char	*str)
{
	int	len;
	int	i;
	char	*ret;

	i = 0;
	while (str[i])
		i++;
	len = i;
	ret = malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i = -1;
	while(++i < len)
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}

static char	*ft_strndup(const char	*str, int len)
{
	int i;
	char	*ret;

	ret = malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i = -1;
	while(++i < len)
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}

static int	is_token(char c)
{
	return (c == '\"' || c == '\'' || c == '$' || c == '=' ||
			c == '>' || c == '<' || c == '|' || c == '\n');
}

static char	*expand_dollar(char *token_value) // ADD ONLY $? NOT $_ OR $$ add struct for it
{
	char	*ret;
	char	*trim;
	int		i;

	i = 0;
	if (!token_value[i + 1] || token_value[i + 1] == ' ' || is_token(token_value[i+1]))
		return (ft_strdup("$"));
	while (token_value[i+1] && token_value[i+1] != ' ' && !is_token(token_value[i+1]))
		i++;
	trim = ft_strndup(token_value + 1, i);
	if (!trim)
		return (NULL);
	ret = getenv(trim);
	free(trim);
	if (!ret)
		return (ft_strdup(""));
	return (ft_strdup(ret));
}

static char	*expand_quote(char *token_value)
{
	char	*ret;
	int		len;
	
	len = 0;
	while (token_value[len])
		len++;
	ret = malloc(len - 1);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, token_value + 1, len - 2);
	ret[len - 2] = '\0';
	return (ret);
}

static int	ft_strlen(const char *str)
{
	const char	*p;
	
	p = str;
	while (*p)
		p++;
	return (p - str);
}

static char	*expand_dquote(char *token_value)
{
	char	*ret;
	int		len;
	int		i;
	char	**env_vars;
	int		j;
	
	i = -1;
	len = 0;
	while (token_value[++i])
		if (token_value[i] == '$')
			len++;
	env_vars = (char **)malloc(sizeof(char *) * len+1);
	if (!env_vars)
		return (NULL);
	env_vars[len] = 0;
	len = 0;
	j = 0;
	i = -1;
	while (token_value[++i])
	{
		if (token_value[i] == '$')
		{
			env_vars[j] = expand_dollar(token_value + i);
			if (!env_vars[j])
				return (NULL);
			len += ft_strlen(env_vars[j]);
			while (token_value[i + 1] && token_value[i + 1] != ' ' && !is_token(token_value[i + 1]))
				i++;
			j++;
		}
		else
			len++;			
	}
	j = -1;
	ret = malloc(sizeof(char *) * len - 1);
	ret[len - 2] = '\0';
	i = 0;
	j = 1;
	while (--len > 1)
	{
		printf("current: %c\n", token_value[j]);
		if (token_value[j] == '$')
		{
			while (**env_vars)
			{
				ret[i] = **env_vars;
				i++;
				(*env_vars)++;
			}
			j++;
			while (token_value[j] && token_value[j] != ' ' && !is_token(token_value[j]))
				j++;
			(env_vars)++;
		}
		else
			ret[i++] = token_value[j++];
	}
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
