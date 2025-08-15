/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:31:37 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/14 01:31:53 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	set_env(char *cwd)
{
	char	*pwd_var;
	char	*oldpwd;

	pwd_var = getenv("PWD");
	if (pwd_var)
	{
		oldpwd = ft_strjoin("OLDPWD=", pwd_var);
		collect_malloc(oldpwd, CHECK);
		if (getenv("OLDPWD"))
			change_var(oldpwd);
		else
			add_var(oldpwd);
		collect_malloc(oldpwd, DELETE);
	}
	oldpwd = ft_strjoin("PWD=", cwd);
	collect_malloc(oldpwd, CHECK);
	if (pwd_var)
		change_var(oldpwd);
	else
		add_var(oldpwd);
	collect_malloc(oldpwd, DELETE);
	return (0);
}

static int	change_dir(char *dirname)
{
	char	*cwd;

	if (chdir(dirname))
	{
		print_err3("cd", dirname, strerror(errno));
		return (-1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		print_err3("getcwd", "couldn't get current or parent working directory", strerror(errno));
		return (0);
	}
	collect_malloc(cwd, ENV_CHECK);
	pwd(cwd);
	set_env(cwd);
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
	if (change_dir(args[1]))
		return (1);
	return (0);
}
