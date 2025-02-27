/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:05:28 by obastug           #+#    #+#             */
/*   Updated: 2025/02/26 16:12:56 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

void	print_token(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != TOKEN_EON && tokens[i].value)
	{
		if (i != 0)
			putchar(' ');
		if (tokens[i].type != TOKEN_SKIP)
			printf("%s", tokens[i].value);
		i++;
	}
	putchar('\n');
}

void	print_str_list(char	**str_list)
{
	int	i;

	i = 0;
	while (str_list[i])
	{
		if (i != 0)
			putchar(' ');
		printf("%s", str_list[i]);
		i++;
	}
	putchar('\n');
}

void	print_node(t_astnode *node)
{
	printf("---\n");
	if (node->type == NODE_COMMAND)
	{
		printf("node type: command\n");
		//print_token(node->tokens);
		printf("execute path: '%s'\n", node->path);
		print_str_list(node->args);
	}
	else if (node->type == NODE_PIPE)
		printf("node type: pipe\n");
	else if (node->type == NODE_REDIRECT)
	{
		printf("node type: redirect\n");
		printf("to file %s\n", node->file);
	}
	else if (node->type == UNINITIALIZED)
	{
		printf("node type: uninitialized\n");
		print_token(node->tokens);
	}
	printf("---\n");
	return ;
}

void	print_asttree(t_astnode *parent)
{
	if (parent)
		print_node(parent);
	else
		return ;
	if (parent->left)
		print_asttree(parent->left);
	if (parent->right)
		print_asttree(parent->right);
	return ;
}
