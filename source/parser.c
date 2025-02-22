/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:29:28 by obastug           #+#    #+#             */
/*   Updated: 2025/02/23 01:38:30 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>
#include "parser.h"
#include <stdio.h>

//first we initialize first node
//then we send it to the parser
//returns itself

//only pipe can have children

void	free_asttree(t_astnode *root)
{
	free(root->command);
	if (root->left)
		free_asttree(root->left);
	if (root->right)
		free_asttree(root->right);
	free(root);
}

t_astnode	*init_node(t_token *token)
{
	t_astnode	*node;

	node = malloc(sizeof(t_astnode));
	if (!node)
		return (NULL);
	node->tokens = token;
	node->file = NULL;
	node->left = NULL;
	node->right = NULL;
	node->type = UNINITIALIZED;
	node->redirect_type = 0;
	return (node);
}

t_astnode	*parser(t_astnode *root)
{
	parse_pipe(root);
	parse_redirect(root);
	parse_command(root);
	print_asttree(root);
	return (root);
}