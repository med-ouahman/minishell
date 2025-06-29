/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:53:12 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/28 11:20:07 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/signal_handler.h"

void	signal_handler(int signum)
{
	struct sigaction	act;

	if (SIGINT == signum)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (SIGQUIT == signum)
	{
		memset(&act, 0, sizeof act);
		act.sa_handler = SIG_IGN;
		sigaction(signum, &act, NULL);
	}
}
