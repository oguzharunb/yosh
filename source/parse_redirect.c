/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:59:22 by obastug           #+#    #+#             */
/*   Updated: 2025/02/23 01:05:57 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

//when a redirection comes by
t_astnode	*redirect(t_astnode *node, int i)
{
	node->left = init_node(node->tokens);
	if (!node->left)
		return (NULL);
	node->file = node->tokens[i + 1].value;
	node->redirect_type = node->tokens[i].type;
	node->type = NODE_REDIRECT;
	node->tokens[i].type = TOKEN_SKIP;
	node->tokens[i + 1].type = TOKEN_SKIP;
	return (node);
}

t_astnode	*parse_redirect(t_astnode *root)
{
	int	i;
	int	breakpoint;

	i = 0;
	breakpoint = -1;
	if (!root)
		return (NULL);
	while (root->type == UNINITIALIZED && root->tokens[i].type != TOKEN_EON
			&& root->tokens[i].value)
	{
		if (root->tokens[i].type == TOKEN_DGREAT
				|| root->tokens[i].type == TOKEN_DLESS
				|| root->tokens[i].type == TOKEN_LESS
				|| root->tokens[i].type == TOKEN_GREAT)
			breakpoint = i;
		i++;
	}
	if (root->type == UNINITIALIZED && breakpoint != -1)
		redirect(root, breakpoint);
	parse_redirect(root->left);
	parse_redirect(root->right);	
	return (root);
}
