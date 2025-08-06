/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:46:53 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/02 11:11:52 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd && errno == ENOMEM)
	{
		collect_malloc(NULL, DESTROY);
		return (1);
	}
	if (!cwd)
	{
		print_err2("pwd", strerror(errno));
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
