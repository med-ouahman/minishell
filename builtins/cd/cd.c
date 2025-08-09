/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:51:06 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/08 11:56:54 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	change_dir(char *dirname)
{
	char	*cwd;

	if (chdir(dirname))
	{
		print_err3("cd", dirname, strerror(errno));
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		print_err2("cd", strerror(errno));
		return (-1);
	}
	collect_malloc(cwd, ENV_CHECK);
	pwd(cwd);
	return (0);
}

int	cd(char **args)
{
	if (args[1] == NULL)
	{
		print_err2("cd", "too few arguments");
		return (1);
	}
	if (args[2] != NULL)
	{
		print_err2("cd", "too many arguments");
		return (1);
	}
	change_dir(args[1]);
	return (0);
}
