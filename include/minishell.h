/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:20:37 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/07 04:58:27 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\033[1;32mmini@0.0.0$ \033[0m"
# define ERROR_PROMPT "\033[31mmini@0.0.0$ \033[0m"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./builtins.h"
# include "./signal_handler.h"
# include "./executor.h"



#endif