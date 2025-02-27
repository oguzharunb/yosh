/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:43:36 by obastug           #+#    #+#             */
/*   Updated: 2025/02/27 19:20:31 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "executer.h"
#include <unistd.h>
// | stdout -> stdin
// > stdout -> fd
// < fd -> stdin
// >> stdout -> fd
// << stdin -> 

int	execute_tree(t_astnode *root, t_enviroment *env)
{
	(void)env;
	find_path_for_command(root);
	return (1);
}