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

#include "../../include/builtins.h"

int	pwd(char *oldpwd)
{
	static char	*cwd;

	if (!cwd)
	{
		cwd = getcwd(NULL, 0);
		collect_malloc(cwd, ENV_CHECK);
	}
	if (oldpwd)
	{
		collect_malloc(cwd, ENV_DELETE);
		cwd = oldpwd;
		return (0);
	}
	printf("%s\n", cwd);
	return (0);
}
