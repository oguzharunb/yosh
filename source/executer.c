/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:43:36 by obastug           #+#    #+#             */
/*   Updated: 2025/02/26 15:41:08 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "executer.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

// | stdout -> stdin
// > stdout -> fd
// < fd -> stdin
// >> stdout -> fd
// << stdin -> 

extern char **__environ;
// assuming node is type of NODE_COMMAND
// return -1 on error
int	execute_command_node(t_astnode *node)
{
	char	**env = __environ;
	if (execve(node->path, node->args, env) == -1)
	{
		perror("execve");
		return (-1);
	}
	return (0);
}

// 2 -> execution error
// 1 -> no node
int	execute_valid_tree(t_astnode *node)
{
	if (!node)
		return (1);
	execute_valid_tree(node->left);
	execute_valid_tree(node->right);
	if (node->type == NODE_COMMAND)
	{
		if (execute_command_node(node) == -1)
		{
			perror("execute_command_node");
			return (2);
		}
	}
	return (0);
}

// returns 0 on success
// returns 1 on error
int	execute(t_astnode *root)
{
	if (!find_path_for_command(root))
	{
		perror("find_path_for_command");
		return (1);
	}
	if (execute_valid_tree(root))
	{
		perror("execute_valid_tree");
		return (1);
	}
	return (0);
}