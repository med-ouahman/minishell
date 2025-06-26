/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:53:12 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/26 10:35:02 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/signal_handler.h"

int	sig;

void	signal_handler(int signum)
{
	if (SIGINT == signum)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		// exit(0);
	}
	if (SIGSTOP == sig)
	{

	}
}
