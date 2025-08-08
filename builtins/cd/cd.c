/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:51:06 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/07 05:28:40 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	set_env(char *key_var)
{
	char	*new_pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		print_err2("cd", strerror(errno));
		return (1);
	}
	new_pwd = ft_strjoin(key_var, cwd);
	free(cwd);
	collect_malloc(new_pwd, ENV_CHECK);
	change_var(new_pwd);
	return (0);
}

static int	change_dir(char *dirname)
{
	if (chdir(dirname))
	{
		print_err3("cd", dirname, strerror(errno));
		return (1);
	}
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
	if (set_env("OLDPWD=") || change_dir(args[1]) || set_env("PWD="))
		return (1);
	return (0);
}
