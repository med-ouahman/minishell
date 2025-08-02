/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 04:32:21 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/02 04:32:42 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

#define PROMPT "\033[1;32mmini@0.0.0$ \033[0m"
#define ERROR_PROMPT "\033[31mmini@0.0.0$ \033[0m"
#define RED_START "\033[31m"

#define RED_END "\033[0m"

#define GREEN_START "\033[1;32m"
#define GREEN_END "\033[0m"

char	*current_dir(char *prompt, t_uint size)
{
	char	*pwd;
	char	*start;
	char	*end;

	start = GREEN_START;
	end = GREEN_END;
	if (access_exit_code(0, READ))
	{
		start = RED_START;
		end = RED_END;
	}
	pwd = getenv("PWD");
	if (!pwd || ft_strlen(pwd) > 50)
	{
		if (access_exit_code(0, READ))
			return (ERROR_PROMPT);
		return (PROMPT);
	}
	pwd = ft_strrchr(pwd, '/') + 1;
	ft_strlcat(prompt, start, size);
	ft_strlcat(prompt, pwd, size);
	ft_strlcat(prompt, "$ ", size);
	ft_strlcat(prompt, end, size);
	return (prompt);
}
