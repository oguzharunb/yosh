/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:59:22 by obastug           #+#    #+#             */
/*   Updated: 2025/02/22 13:59:43 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

//when a redirection comes by
t_astnode	*redirect(t_astnode *node, int i)
{
	node->left = init_node(node->tokens);
	if (!node->left)
		return (NULL);
	node->file = node->tokens[i + 1].value;
	node->redirect_type = node->tokens[i].type;
	node->type = NODE_COMMAND;
	node->tokens[i].type = TOKEN_SKIP;
	node->tokens[i + 1].type = TOKEN_SKIP;
}

t_astnode	*parse_redirect(t_astnode *root)
{
	return (root);
}

t_astnode	*parse(t_astnode *root)
{

//		if (root->tokens[i].type == TOKEN_DGREAT
//				|| root->tokens[i].type == TOKEN_DLESS
//				|| root->tokens[i].type == TOKEN_LESS
//				|| root->tokens[i].type == TOKEN_GREAT)
//			redirect(root, i);
	return (root);
}