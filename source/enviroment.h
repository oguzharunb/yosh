/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 06:08:59 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/27 19:16:38 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_VARIABLES_H
# define ENVIROMENT_VARIABLES_H

typedef struct s_node
{
	char	*key;
	char	*value;
	int		export_lock;
	/* EXPORT LOCK (if export lock = 1 dont export var)
	in shell enviroment not all
	enviroment varables exported to child processes.
	*Commonly Exported Variables
		**PATH: Specifies the directories in which executable programs are located.
		**HOME: The home directory of the current user.
		**USER: The name of the current user.
		**SHELL: The path to the current user's shell.
		**PWD: The current working directory.
		**OLDPWD: The previous working directory.
		**LANG: The current locale.
		**TERM: The type of terminal to emulate.
	*Variables Typically Not Exported
		**Internal Shell Variables: Variables used internally by the shell
		that do not need to be available to child processes.
		**Temporary Variables: Variables that are only needed for the duration
		of the current shell session or script.
	*/
	struct s_node	*next;
}		t_node;

typedef struct s_enviroment
{
	struct	s_node	*top;
	struct	s_node	*bottom;
}		t_enviroment;

int		setup_enviroment(t_enviroment *env);
int		setup_paths(t_enviroment *env);
char	*get_cwd(t_enviroment *env);
t_node	*find_variable(t_enviroment *env, char *key);
void	delete_variable(t_enviroment *env, char *key);
int		revalue_variable(t_enviroment *env, char *key, char *value, int lock);
int		add_variable(t_enviroment	*env, char *key, char *value, int lock);
int		clear_enviroment(t_enviroment *env);

#endif