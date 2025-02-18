/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:06:17 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/18 05:37:36 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

static int	is_token(char c)
{
	return (c == '\"' || c == '\'' || c == '$' || c == '=' ||
			c == '>' || c == '<' || c == '|' || c == '\n');
}

static void pass_token(char token, char **str)
{
	if (token == '>' || token == '<')
	{
		if ((*((*str)+1)) == token)
			(*str)++;
	}
	else if (token == '\'' || token == '\"')
	{
		(*str)++;
		while ((**str) != token)
			(*str)++;
	}
	else if (token == '$')
	{
		(*str)++;
		while (**str && **str != ' ' && !is_token(*(*str+1)))
			(*str)++;
	}
}
static int	count_tokens(char *str)
{
	int	is_compound;
	int	count;
	
	count = 0;
	is_compound = 0;
	while (*str)
	{
		if (is_token(*str))
		{
			pass_token(*str, &str);
			is_compound = 0;
			count++;
		}
		else if (*str == ' ' && is_compound)
			is_compound = 0;
		else if (*str != ' ' && !is_compound)
		{
			is_compound = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static char	*token_dup(const char *s, size_t size)
{
	char	*dup;
	size_t	i;

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

static void	split_tokens(char **tokens, char **str)
{
	char	*p;

	if (is_token(**str))
	{
		p = *str;
		pass_token(**str, str);
		*tokens = token_dup(p, ((*str) + 1) - p);
		(*str)++;
	}
	else if (**str != ' ')
	{
		p = *str;
		while (**str && !is_token(**str) && **str != ' ')
			(*str)++;
		*tokens = token_dup(p, (*str) - p);
	}
	else
		(*str)++;
}

static int	strcomp(char *str1, char *str2)
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

static void	insert_types(t_token **tokens)
{
	if (strcomp((*tokens)->value, ">"))
		(*tokens)->type = TOKEN_GREAT;
	else if (strcomp((*tokens)->value, "<"))
		(*tokens)->type = TOKEN_LESS;
	else if (strcomp((*tokens)->value, ">>"))
		(*tokens)->type = TOKEN_DGREAT;
	else if (strcomp((*tokens)->value, "<<"))
		(*tokens)->type = TOKEN_DLESS;
	else if (strcomp((*tokens)->value, "|"))
		(*tokens)->type = TOKEN_PIPE;
	else if (strcomp((*tokens)->value, "\n"))
		(*tokens)->type = TOKEN_NEWLINE;
	else
		(*tokens)->type = TOKEN_WORD;
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		number_of_tokens;
	int		i;
	
	number_of_tokens = count_tokens(input);
	tokens = (t_token *)malloc(sizeof(t_token) * (number_of_tokens + 1));
	if (!tokens)
		exit (1);
	i = -1;
	while (*input)
	{
		if (*input == ' ')
			input++;
		else
			split_tokens(&(tokens[++i].value), &input);
	}
	tokens[++i].value = NULL;
	insert_types(&tokens);
	i = -1;
	while (tokens[++i].value)
		printf("%s\n", tokens[i].value);
	return (tokens);
}
