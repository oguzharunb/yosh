/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:01:22 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/16 18:44:45 by obastug          ###   ########.fr       */
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