/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 23:29:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/26 23:49:24 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"
#include "str.h"
#include <stdlib.h>
#include <unistd.h>

t_node	*find_variable(t_enviroment *env, char *key)
{
	t_node	*ret;

	ret = env->top;
	while (ret)
	{
		if (ft_strcmp(ret->key, key))
			return (ret);
		ret = ret->next;
	}
	return (NULL);
}

void	delete_variable(t_enviroment *env, char *key, char *value, int lock)
{
	t_node	*prev;
	t_node	*to_delete;

	to_delete = env->top;
	prev = NULL;
	while (to_delete)
	{
		if (ft_strcmp(to_delete->key, key))
		{
			if (prev)
				prev->next = to_delete->next;
			else
				env->top = to_delete->next;
			if (to_delete == env->bottom)
				env->bottom = prev;
			free(to_delete->key);
			free(to_delete->value);
			free(to_delete);
			return ;
		}
		prev = to_delete;
		to_delete = to_delete->next;
	}
}

int	revalue_variable(t_enviroment *env, char *key, char *value, int lock)
{
	t_node	*node;

	node = find_variable(env, key);
	if (!node)
		return (-1);
	free(node->value);
	node->value = ft_strdup(value);
	if (!node->value)
		return (-1);
	node->export_lock = lock;
	return (0);
}

int	add_variable(t_enviroment	*env, char *key, char *value, int lock)
{
	t_node	*new;
	t_node	*tmp;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (-1); // malloc err
	new->key = ft_strdup(key);
	if (!new->key)
		return (-1);
	new->value = ft_strdup(value);
	if (!new->value)
		return (-1);
	new->export_lock = lock;
	new->next = NULL;
	if (!env->top)
	{
		env->top = new;
		env->bottom = new;
		return (0);
	}
	env->bottom->next = new;
	env->bottom = new;
	return (0);
}

int	clear_enviroment(t_enviroment *env)
{
	t_node	*tmp;
	
	while (env->top)
	{
		tmp = env->top;
		env->top = env->top->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	return (-1); // return enviroment error equivalent error code.
}
