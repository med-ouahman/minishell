/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:53:12 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/20 15:55:29 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/signal_handler.h"

int	sig;

void	exit(int status);

void	signal_handler(int signum)
{
	if (SIGINT == signum)
	{
		exit(0);
		rl_on_new_line();
	}
	if (SIGSTOP == sig)
	{

	}
}
