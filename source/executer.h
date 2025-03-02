/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:28:21 by obastug           #+#    #+#             */
/*   Updated: 2025/02/27 12:14:25 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "enviroment.h"
int	find_path_for_command(t_astnode *node);
int	execute_tree(t_astnode *root, t_enviroment *env);

#endif