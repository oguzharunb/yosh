/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:43:36 by obastug           #+#    #+#             */
/*   Updated: 2025/03/14 12:39:04 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "executer.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include "enviroment.h"
#include <stdlib.h>
#include <fcntl.h>

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

//-2 no node
//-1 no file
int	execute_redirect(t_astnode *node, int redirect_to, int redirect_from)
{
	int		fd;
	pid_t	pid;
	if (!node)
		return (-2);
	if (node->redirect_type == TOKEN_GREAT)
	{
		if (redirect_to == STDIN_FILENO)
		{
			fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			redirect_to = fd;
			write(fd, NULL, 0);
		}
		if (node->left && node->left->type == NODE_REDIRECT)
		{
			execute_redirect(node->left, redirect_to, redirect_from);
		}
		else if (node->left && node->left->type == NODE_COMMAND)
		{
			pid = fork();
			if (pid == 0)
			{
				dup2(redirect_from, STDIN_FILENO);
				dup2(redirect_to, STDOUT_FILENO);
				close(redirect_to);
				close(redirect_to);
				execute_command_node(node->left);
				exit(0);
			}
			else
			{
				close(redirect_to);
				close(redirect_to);
				waitpid(pid, NULL, 0);
			}
		}
	}
	if (node->redirect_type == TOKEN_DGREAT)
	{
		if (redirect_to == STDIN_FILENO)
		{
			fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
			redirect_to = fd;
		}
		if (node->left && node->left->type == NODE_REDIRECT)
		{
			execute_redirect(node->left, redirect_to, redirect_from);
		}
		else if (node->left && node->left->type == NODE_COMMAND)
		{
			pid = fork();
			if (pid == 0)
			{
				dup2(redirect_from, STDIN_FILENO);
				dup2(redirect_to, STDOUT_FILENO);
				close(redirect_to);
				close(redirect_to);
				execute_command_node(node->left);
				exit(0);
			}
			else
			{
				close(redirect_to);
				close(redirect_to);
				waitpid(pid, NULL, 0);
			}
		}
	}
	else if (node->redirect_type == TOKEN_LESS)
	{
		if (redirect_from == STDOUT_FILENO)
		{
			fd = open(node->file, O_RDONLY, 0666);
			redirect_from = fd;
		}
		if (node->left && node->left->type == NODE_REDIRECT)
		{
			execute_redirect(node->left, redirect_to, redirect_from);
		}
		else if (node->left && node->left->type == NODE_COMMAND)
		{
			pid = fork();
			if (pid == 0)
			{
				dup2(redirect_from, STDIN_FILENO);
				dup2(redirect_to, STDOUT_FILENO);
				close(redirect_from);
				close(redirect_to);
				execute_command_node(node->left);
				exit(0);
			}
			else
			{
				close(redirect_from);
				close(redirect_to);
				waitpid(pid, NULL, 0);
			}
		}
	}
	return (0);
}

void	execute_pipe(t_astnode *node)
{
	int pipedes[2]; // File descriptors for the pipe
	pid_t	pid;
		// Create a pipe

	pipe(pipedes);
	// Fork the process
	pid = fork();
	if (pid == 0)
	{
		close(pipedes[0]); // Close the read end of the pipe
		dup2(pipedes[1], STDOUT_FILENO); // Redirect stdout to the write end of the pipe
		if (node && node->left && node->left->type == NODE_PIPE)
		{
			execute_pipe(node->left);
		}
		else if (node && node->left && node->left->type == NODE_COMMAND)
		{
			execute_command_node(node->left);
		}
		close(pipedes[1]); // Close the write end after duplicating
		exit(0);
	}
	if (pid)
	{
		close(pipedes[1]); // Close the write end of the pipe
		dup2(pipedes[0], STDIN_FILENO); // Redirect stdin to the read end of the pipe
		execute_command_node(node->right);
		close(pipedes[0]); // Close the read end after duplicating
	}
}

// 3 -> systemcall error
// 2 -> execution error
// 1 -> no node
int	execute_valid_tree(t_astnode *node)
{
	pid_t	pid;

	if (!node)
		return (1);
	if (node->type == NODE_PIPE)
	{
		pid = fork();
		if (pid == 0)
		{
			execute_pipe(node);
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}
	else if (node->type == NODE_REDIRECT)
	{
		execute_redirect(node, STDIN_FILENO, STDOUT_FILENO);
	}
	else if (node->type == NODE_COMMAND)
	{
		pid = fork();
		if (pid == 0)
			execute_command_node(node);
		else
			waitpid(pid, NULL, 0);
	}
	return (0);
}

// returns 0 on success
// returns 1 on error
int	executer(t_astnode *root, t_enviroment *env)
{
	(void)env;
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