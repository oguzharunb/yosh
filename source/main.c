/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:01:22 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/19 07:04:48 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"

static int	check_sequence_complete(char *input)
{
	int	quote;
	int	dquote;

	if (!input || !(*input))
		return (0);
	quote = 0;
	dquote = 0;
	while (*input)
	{
		if (*input == '\"' && !(quote))
			dquote = !(dquote);
		if (*input == '\'' && !(dquote))
			quote = !(quote);
		input++;
	}
	return (quote || dquote);
}

void free_tokens(t_token *tokens)
{
    int i = 0;
    while (tokens[i].value)
    {
        free(tokens[i].value);
        i++;
    }
    free(tokens);
}

void	expander(t_token *tokens);

int main(void)
{
	char	*input;
	t_token *tokens;
	
	while (1)
	{
		//input = get_input(); // checks if input completed
		input = readline("yosh1> "); // YEAP IT HAS LEAKS THAT WE CANT HANDLE -> https://cboard.cprogramming.com/c-programming/136521-memory-leak-readline.html
		if (!input)
			exit(1);
		if (check_sequence_complete(input))
		/* err according to subject : • Not interpret
		unclosed quotes or special characters 
		which are not required by the subject 
		such as \ (backslash) or ; (semicolon). */
		{
			free(input);
			exit(1); // clear and exit ofc -- later implement
		}
		if (!strcmp(input, "exit"))	break; // exit is also a command so delete this line
		tokens = lexer(input);
		if (!tokens->value)
		{
			free(input);
			continue;
		}
		add_history(input);
		printf("here\n");
		expander(tokens); /* deletes quotes and dquotes
						and gets env variables */
		int i = -1;
		printf("here2\n");
		while (tokens[++i].value)
			printf("%s\n", tokens[i].value);
		//	parser
		//	executer
		free(input);
	}
	rl_clear_history();
	free(input);
	return (0);
}