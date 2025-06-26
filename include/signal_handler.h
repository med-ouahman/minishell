/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:01:57 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/26 10:33:51 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>

int	    new_prompt(char **line, char *prompt);
void	signal_handler(int signum);

#endif
