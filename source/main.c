/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:01:22 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/18 05:47:37 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"

char	*get_input(void);

int main(void)
{
	char	*input;
	t_token *tokens;
	
	while (1)
	{
		input = get_input(); // checks if input completed
		if (!input)
			exit(2); // err
		if (!strcmp(input, "exit"))	break;
		printf("promt: %s\n", input);
		tokens = lexer(input);
		if (!tokens->value)
			continue;
		add_history(input);
		printf("here\n");
		//	continue;
		//	parser
		//	executer
		free(input);
	}
}