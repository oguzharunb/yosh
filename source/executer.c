/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:43:36 by obastug           #+#    #+#             */
/*   Updated: 2025/02/27 12:14:11 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "executer.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include "enviroment.h"
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
	int		pid;

	pid = fork();
	if (pid == 0 && execve(node->path, node->args, env) == -1)
	{
		perror("execve");
		return (-1);
	}
	if (pid)
	{
		waitpid(pid, NULL, 0);
	}
	return (0);
}

// 3 -> systemcall error
// 2 -> execution error
// 1 -> no node
int	execute_valid_tree(t_astnode *node)
{
	int	pipedes[2];
	if (!node)
		return (1);
	if (node->type == NODE_PIPE)
	{
		printf("redirected\n");
		if (pipe(pipedes) == -1)
		{
			perror("pipe");
			return (3);
		}
		close(pipedes[0]);
		if (dup2(pipedes[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (3);
		}
		close(pipedes[1]);
	}
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
		printf("command not found\n");
		return (1);
	}
	if (execute_valid_tree(root))
	{
		perror("execute_valid_tree");
		return (1);
	}
	return (0);
}