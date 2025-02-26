/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:05:09 by obastug           #+#    #+#             */
/*   Updated: 2025/02/26 15:11:34 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include "str.h"
#include "parser.h"

int is_file_executable(const char *file_path)
{
    struct stat sb;

	if (!ft_strchr(file_path, '/'))
		return (0);
    if (stat(file_path, &sb) == 0 && S_ISREG(sb.st_mode)
			&& (sb.st_mode & S_IXUSR))
        return (1);
    return (0);
}

char	*is_file_executable_in_path(char **path_list, char *file_path)
{
	int		i;
	char	*final_path;

	i = 0;
	while (path_list[i])
	{
		final_path = ft_strjoin(path_list[i], file_path);
		if (!final_path)
		{
			perror("ft_strjoin");
			return (NULL);
		}
		if (is_file_executable(final_path))
			return (final_path);
		else
			free(final_path);
		i++;
	}
	return (NULL);
}

char	*search_executable_path(char *file_path)
{
	char	*env_path;
	char	**path_list;
	char	*final_path;

	if (is_file_executable(file_path))
		return (file_path);
	env_path = getenv("PATH");
	if (!env_path)
	{
		perror("Environment PATH couldnt found.");
		return (NULL);
	}
	path_list = ft_split(env_path, ':');
	if (!path_list)
	{
		perror("ft_split");
		free(env_path);
		return (NULL);
	}
	final_path = is_file_executable_in_path(path_list, file_path);
	free_str_list(path_list);
	return (final_path);
}

// 0 -> if command not found
// 1 -> if command path successfully found
// 2 -> node doesnt exists
int	find_path_for_command(t_astnode *node)
{
	char	*path;
	if (!node)
		return (2);
	else if (node->type == NODE_COMMAND)
	{
		path = search_executable_path(node->args[0]);
		if (NULL)
		{
			perror("search executable path");
			return (0);
		}
		node->path = path;
	}
	find_path_for_command(node->left);
	find_path_for_command(node->right);
	return (1);
}