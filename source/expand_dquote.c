/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 05:48:02 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/23 07:19:25 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_strlen(const char *str);
int		is_token(char c);
char	*expand_dollar(char *token_value);

static int	count_dollars(const char *str)
{
	int	ret;

	ret = 0;
	while (*str)
	{
		if (*str == '$')
			ret++;
		str++;
	}
	return (ret);
}

static int	get_env_vars(char *token_value, int *len, char **env_vars)
{
	int		i;
	int		j;

	*len = 0;
	i = -1;
	j = 0;
	while (token_value[++i])
	{
		if (token_value[i] == '$')
		{
			env_vars[j] = expand_dollar(token_value + i);
			if (!env_vars[j])
				return (1);
			(*len) += ft_strlen(env_vars[j]);
			while (token_value[i + 1] && token_value[i + 1] != ' ' && !is_token(token_value[i + 1]))
				i++;
			j++;
		}
		else
			(*len)++;			
	}
	return (0);
}

static void	place_env_vars(char *token_val, char **env_vars, char *expanded)
{
	int	i;
	int	j;
	
	i = 0;
	j = 1;
	while (*env_vars)
	{
		if (token_val[j] == '$')
		{
			while (**env_vars)
			{
				expanded[i] = **env_vars;
				i++;
				(*env_vars)++;
			}
			j++;
			while (token_val[j] && token_val[j] != ' ' && !is_token(token_val[j]))
				j++;
			(env_vars)++;
		}
		else
			expanded[i++] = token_val[j++];
	}
}
char	*expand_dquote(char *token_value)
{
	char	*ret;
	char	**env_vars;
	int		len;
	
	len = count_dollars(token_value);
	env_vars = (char **)malloc(sizeof(char *) * (len + 1));
	if (!env_vars)
		return (NULL);
	env_vars[len] = NULL;
	if (get_env_vars(token_value, &len, env_vars))
		return (NULL);
	ret = malloc(sizeof(char *) * (len - 1));
	if (!ret)
		return (NULL);
	place_env_vars(token_value, env_vars, ret);
	ret[len - 2] = '\0';
	return (ret);
}
