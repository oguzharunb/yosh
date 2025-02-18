/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:29:28 by obastug           #+#    #+#             */
/*   Updated: 2025/02/18 22:20:10 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

// returns -1 if there is a pipe error
int	get_command_num(t_token *input)
{
	int	i;
	int	command_num;
	int	in_command;

	in_command = 0;
	i = 0;
	command_num = 0;
	while (input[i].value)
	{
		if (input[i].type != TOKEN_PIPE)
		{
			command_num++;
			in_command = 1;
		}
		else
		{
			if (in_command == 0)
				return (-1);
			in_command = 0;
		}
		i++;
	}
	return (command_num);
}

t_token	**token_to_command_list(t_token *input)
{
	t_token	**command_list;
	int		command_num;
	int		i;
	int		j;
	int		command;

	command_num = get_command_num(input);
	if (command_num == -1)
		return (NULL);
	command_list = malloc(sizeof(t_token *) * command_num + 1);
	i = 0;
	command = 0;
	while (input[i].value)
	{
		j = 0;
		while (input[i + j].type != TOKEN_PIPE)
			j++;
		command_list[command] = input + i;
		input[i + j].value = TOKEN_EOC;
	}
}