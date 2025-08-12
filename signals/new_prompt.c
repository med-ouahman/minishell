/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:28:48 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/12 04:20:29 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/signal_handler.h"

void	rl_new_prompt(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	exit_heredoc(int signum)
{
	access_exit_code(128 + signum, WRITE);
	close(heredoc_read_fd(0, READ));
	cleanup(access_exit_code(128 + signum, WRITE));
}
