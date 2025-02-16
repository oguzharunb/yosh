/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:06:17 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/16 19:39:33 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//boşluklarla ayıracaz
//unless tırnak ya da çift tırnak gelene kadar
//şslfkşslfkgsdflgksdfglsd  "hello world"
// durdurucular ekle arraye

int	lexer(char *input)
{
	int	i;
	int	j;
	int	sequence;

	i = 0;
	sequence = 0;
	while (input[i])
	{
		j = 0;
		if (input[i + j] == '\"' || input[i + j] == '\'')
			sequence = !sequence;
		if (input[i + j] == ' ' && sequence == 0)
		{
			write(1, input + i, j);
			i += j;	
		}
		j++;
	}
}