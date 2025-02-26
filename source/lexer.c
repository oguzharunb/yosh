/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:06:17 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/26 13:06:49 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

int	is_token(char c);
int	ft_strcmp(char *str1, char *str2);
char	*token_dup(const char *s, size_t size);

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
		while (*((*str) + 1) && *((*str) + 1) != ' ' && !is_token(*((*str) + 1)))
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

static void	insert_types(t_token *tokens)
{
	int	i;
	
	i = 0;
	while (tokens[i].value)
	{
		if (ft_strcmp((tokens + i)->value, ">"))
			(tokens + i)->type = TOKEN_GREAT;
		else if (ft_strcmp((tokens + i)->value, "<"))
			(tokens + i)->type = TOKEN_LESS;
		else if (ft_strcmp((tokens + i)->value, ">>"))
			(tokens + i)->type = TOKEN_DGREAT;
		else if (ft_strcmp((tokens + i)->value, "<<"))
			(tokens + i)->type = TOKEN_DLESS;
		else if (ft_strcmp((tokens + i)->value, "|"))
			(tokens + i)->type = TOKEN_PIPE;
		else if (ft_strcmp((tokens + i)->value, "\n"))
			(tokens + i)->type = TOKEN_NEWLINE;
		else
			(tokens + i)->type = TOKEN_WORD;
		i++;
	}
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
	insert_types(tokens);
	return (tokens);
}
