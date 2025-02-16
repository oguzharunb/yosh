/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:01:22 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/17 01:24:30 by yusudemi         ###   ########.fr       */
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
		input = get_input(); // checks if input completed
		if (!input)
			exit(2); // err
		if (!input)	printf("\n");
		else	add_history(input);
		if (!strcmp(input, "exit"))	break;
		printf("promt: %s\n", input);
		//	lexer
		//if (!lexer)
		//	continue;
		//	parser
		//	executer
		free(input);
	}
}