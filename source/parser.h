/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:00:14 by obastug           #+#    #+#             */
/*   Updated: 2025/02/22 15:41:17 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//NODE_LOGICAL_AND
//NODE_LOGICAL_OR
#include "lexer.h"

typedef enum
{
	UNINITIALIZED,
	NODE_COMMAND,
	NODE_REDIRECT,
	NODE_PIPE
} e_NodeType;
typedef struct s_astnode
{
	e_NodeType				type;
	t_token					*tokens;
	struct s_astnode		*left;
	struct s_astnode		*right;
	char					*file;
	int						redirect_type;
} t_astnode;

void		print_asttree(t_astnode *parent);
void		print_token(t_token *tokens);
t_astnode	*init_node(t_token *token);
void		print_node(t_astnode *node);
t_astnode	*parse_pipe(t_astnode *root);
//file also EOF for heredoc
