/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:16:20 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/06 16:43:38 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	add_to_env(char ***env, char *s)
{
	char			**tmp;
	unsigned int	size;
	unsigned int	i;

	size = size_env(*env);
	i = 0;
	if (!s)
		return (print_file_error("export", "memory allocation"), 1);
	tmp = malloc ((size + 2) * sizeof(char *));
	if (!tmp)
	{
		print_file_error("export", "memory allocation");
		free(s);
		return (1);
	}
	while ((*env)[i])
	{
		tmp[i] = (*env)[i];
		i++;
	}
	tmp[i++] = s;
	tmp[i] = NULL;
	free((*env));
	(*env) = tmp;
	return (0);
}

static int	check_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

static int	change_var(char ***env, char *s, int eq)
{
	unsigned int	i;
	char			*tmp;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp(s, (*env)[i], eq) == 0)
		{
			if (s[eq] == '=' && ((*env)[i][eq] == '=' || !(*env)[i][eq]))
			{
				printf("change value\n");
				tmp = ft_strdup(s);
				if (!tmp)
					return (print_file_error("export", "memory allocation"),
						-1);
				free ((*env)[i]);
				(*env)[i] = tmp;
				return (0);
			}
			else if (s[eq] == (*env)[i][eq] || (*env)[i][eq] == '=')
				return (0);
		}
		i++;
	}
	return (1);
}

static int	check_var(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (1);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[0]) && arg[0] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	export_add(char **vars)
{
	int		n;
	char	*tmp;

	while (*vars)
	{
		tmp = *vars;
		if (check_var(tmp))
			print_file_error2("export", tmp, "not a valid identifier");
		else
		{
			n = change_var(&__environ, tmp, check_equal(tmp));
			if (n < 0)
				return (destroy_env(&__environ), 1);
			else if (n == 0)
				n = 0;
			else if (add_to_env(&__environ, ft_strdup(tmp)))
				return (destroy_env(&__environ), 1);
		}
		vars++;
	}
	return (0);
}
