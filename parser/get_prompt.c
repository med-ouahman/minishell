/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 08:32:04 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/12 08:32:22 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

#define PROMPT "\033[1;32mmini@0.0.0$ \033[0m"
#define ERROR_PROMPT "\033[31mmini@0.0.0$ \033[0m"

char	*get_prompt(void)
{
	if (access_exit_code(0, READ) && access_exit_code(0, READ) != 130)
	{
		return (ERROR_PROMPT);
	}
	return (PROMPT);
}
