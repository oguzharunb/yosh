/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 00:12:15 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/27 19:21:26 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <signal.h>

//when ctr-c -> last exit status = 130
void	handle_sigint(int sig)
{
	(void)sig;
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	handle_sigterm(int sig)
{
	(void)sig;
}

int	setup_signal_handlers(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	signal(SIGTERM, handle_sigterm);
	return (0);
}