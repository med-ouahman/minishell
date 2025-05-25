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

#include "../includes/signal_handler.h"

int	sig;

void	signal_handler(int signum)
{
	if (SIGINT == signum)
	{
		printf("\n$ ");
	}
}
