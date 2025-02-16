/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 23:41:54 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/17 01:05:27 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

static int	str_len(const char *str)
{
	const char	*p;

	if (!str)
		return (0);
	p = str;
	while (*p)
		p++;
	return (p - str);
}

static char	*str_join(char *s1, char *s2, int s1_len, int s2_len)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!res)
		return (free((char *)s1), NULL);
	i = 0;
	while (i < s1_len)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < s2_len)
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(s1);
	return (res);
}

static int	check_sequence_complete(char *input, int *quote, int *dquote)
{

	if (!input)
		return (1);
	while (*input)
	{
		if (*input == '\"' && !(*quote))
			*dquote = !(*dquote);
		if (*input == '\'' && !(*dquote))
			*quote = !(*quote);
		input++;
	}
	return (*quote || *dquote);
}

char	*get_input(void)
{
	int	quote;
	int	dquote;
	char	*input;
	char	*ret;

	quote = 0;
	dquote = 0;
	input = NULL;
	ret = NULL;
	while (check_sequence_complete(input, &quote, &dquote))
	{
		if (input)
			free(input);
		if (!input)
			input = readline("yosh1> ");
		if (quote)
			input = readline("quote> ");
		if (dquote)
			input = readline("dquote> ");
		ret = str_join(ret, input, str_len(ret), str_len(input));
	}
	free(input);
	return (ret);
}
