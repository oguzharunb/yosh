/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:19:21 by obastug           #+#    #+#             */
/*   Updated: 2025/02/27 19:08:37 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "str.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "enviroment.h"

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

int	pwd(char **args, t_enviroment *env)
{
	char *buf;
	(void)args;
	(void)env;
	buf = get_cwd(env);
	if (!buf)
		return (1);
	printf("%s\n", buf);
	return (0);
}

void	ft_export(char	**args)
{
	(void)args;
	// use find_variable if it exist use revalue_variable
	// if itsnt use add_variable
	return ;
}

void	unset(char	**args)
{
	(void)args;
	//use delete_variable command after find_variable xd
	return ;
}

void	printenv(char	**args, t_enviroment *env)
{
	t_node	*head;
	(void)args;
	head = env->top;
	while (head)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return ;
}