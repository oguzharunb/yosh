/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:01:22 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/15 01:47:37 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"

int main(int ac, char **av, char **env)
{
	char	*input;
	

	while (1)
	{
		//	Discuss interactive, non-interactive!
		//	if non-interactive shell needed add a get_input function 
		//	checkout isatty function and implement getnextline
		input = readline("minishell> ");
		if (!input)	printf("\n");
		else	add_history(input);
		if (!strcmp(input, "exit"))	break;
		printf("promt: %s\n", input);
		//	lexer
		//	parser
		//	executer
		free(input);
	}
}