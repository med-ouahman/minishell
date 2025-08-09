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

// static int	set_env(char *key_var)
// {
// 	char	*new_pwd;
// 	char	*cwd;

// 	cwd = getcwd(NULL, 0);
// 	if (!cwd)
// 	{
// 		print_err2("cd", strerror(errno));
// 		return (1);
// 	}
// 	new_pwd = ft_strjoin(key_var, cwd);
// 	free(cwd);
// 	collect_malloc(new_pwd, ENV_CHECK);
// 	change_var(new_pwd);
// 	return (0);
// }

static int	change_dir(char *dirname)
{
	char	*pwd_var;
	char	*oldpwd;
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
	pwd_var = getenv("PWD");
	oldpwd = ft_strjoin("OLDPWD=", pwd_var);
	collect_malloc(oldpwd, CHECK);
	change_var(oldpwd);
	collect_malloc(oldpwd, DELETE);
	pwd_var = ft_strjoin("PWD=", cwd);
	collect_malloc(pwd_var, CHECK);
	change_var(pwd_var);
	collect_malloc(pwd_var, DELETE);
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
