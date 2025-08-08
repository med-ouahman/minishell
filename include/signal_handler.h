/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:01:57 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/08 12:07:53 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include <signal.h>
# include <readline/readline.h>
# include "./utils.h"

void	rl_new_prompt(void);
void	sigint_handler(int signum);
void	rl_after_fork(void);
void	handle_signals(void);
void	default_signals(void);
void	ignore_signals(void);
void	sigquit_handler(int signum);

#endif
