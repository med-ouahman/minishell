/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:01:57 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/03 16:01:55 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include <signal.h>
# include <readline/readline.h>
# include "../include/parser.h"
# include <unistd.h>

void	rl_new_prompt(void);
void	sigint_handler(int signum);
void	rl_after_fork(void);
void	handle_signals(void);
void	default_signals(void);
void	ignore_signals(void);

#endif
