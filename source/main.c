/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:01:22 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/27 19:55:36 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"
#include "parser.h"
#include <unistd.h>
#include "executer.h"
#include "str.h"
#include "enviroment.h"

volatile int g_signal;
/*
Be careful. This global variable must only store the signal number
and must not provide any additional information or access to data.
Therefore, using "norm" type structures in the global scope is
forbidden.
*/
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


void	print_tokens(t_token *tokens) // for testing purposes
{
	int i = 0;
	while (tokens[i].value)
	{
		printf("tokens: [%s]\n", tokens[i].value);
		i++;
	}
	printf("END\n");
}

void	print_env(t_enviroment *env) // for testing purposes
{
	t_node *head = env->top;
	while (head)
	{
		printf("key: [%s] value: [%s]\n", head->key, head->value);
		head = head->next;
	}
	printf("END\n");
}

int main(void)
{
	char			*input;
	t_token 		*tokens;
	t_astnode		*root;
	t_enviroment	env;
	
	ft_bzero(&env, sizeof(t_enviroment));
	setup_enviroment(&env);
	if (setup_paths(&env))
		return (-1);
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
		tokens = lexer(input);
		if (!tokens->value)
		{
			free(input);
			continue;
		}
		add_history(input);
		expander(tokens); /* deletes quotes and dquotes
						and gets env variables */
		// print_tokens(tokens); // for testing purposes
		// parser

		root = init_node(tokens);
		if (!root)
		{
			perror("init_node");
			free(input);
		}
		parser(root);
		execute_tree(root, &env);
		free_asttree(root);
		free(input);
		print_env(&env);
	}
	rl_clear_history();
	free(input);
	return (0);
}
