/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:51:06 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/27 13:30:12 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*new_varpwd(char *var)
{
	char	*new_pwd;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (print_file_error("cd", strerror(errno)), NULL);
	new_pwd = ft_strjoin(var, pwd);
	if (!new_pwd)
	{
		print_file_error("cd", "memory allocation");
		free (pwd);
		return (NULL);
	}
	free (pwd);
	return (new_pwd);
}

static int	change_pwd(char ***env, char *oldpwd)
{
	char	*pwd;
	char	*tmp;
	long		i;

	pwd = new_varpwd("PWD=");
	if (!pwd)
		return (1);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], pwd, 4) == 0)
		{
			tmp = (*env)[i];
			(*env)[i] = pwd;
			pwd = tmp;
		}
		else if (ft_strncmp((*env)[i], oldpwd, 7) == 0)
		{
			tmp = (*env)[i];
			(*env)[i] = oldpwd;
			oldpwd = tmp;
		}
		i++;
	}
	return (free(pwd), free(oldpwd), 0);
}

int	cd(char **args)
{
	char	*path;
	char	*oldpwd;

	if (!args[1])
		return (print_file_error("cd", "no path specific"), 1);
	if (args[2])
		return (print_file_error("cd", "too many arguments"), 1);
	path = args[1];
	oldpwd = new_varpwd("OLDPWD=");
	if (!oldpwd)
		return (1);
	if (chdir(path))
	{
		print_file_error2("cd", path, strerror(errno));
		free(oldpwd);
		return (1);
	}
	if (change_pwd(&__environ, oldpwd))
		return (free(oldpwd), 1);
	return (0);
}
