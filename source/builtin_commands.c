/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:19:21 by obastug           #+#    #+#             */
/*   Updated: 2025/02/26 13:40:10 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "str.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	echo(char	**args)
{
	int	i;

	i = 1;
	if (ft_strcmp(args[i], "-n"))
		i++;
	while (args[i])
	{
		if (i != 0)
			ft_putchar(' ');
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		i++;
	}
	if (ft_strcmp(args[i], "-n"))
		putchar('\n');
	return (0);
}

// if no arguments were given go to home directory
// if 1 argument were given go to that directory
int	cd(int argc, char **args)
{
	char	*home_dir;

	home_dir = getenv("HOME");
	if (!home_dir)
		return (1);
	if (argc == 1)
	{
		chdir(home_dir);
		free(home_dir);
	}
	else if (argc == 2)
		chdir(args[1]);
	else
		return (1);
	return (0);
}

int	pwd(char **args)
{
	char	buf[5000];
	
	(void)args;
	ft_bzero(buf, sizeof(buf));
	if (!getcwd(buf, sizeof(buf)))
		return (1);
	printf("%s\n", buf);
	return(0) ;
}

void	ft_export(char	**args)
{
	(void)args;
	return ;
}

void	unset(char	**args)
{
	(void)args;
	return ;
}

void	printenv(char	**args)
{
	extern char	**environ;
	char		**env;

	(void)args;
	env = environ;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return ;
}