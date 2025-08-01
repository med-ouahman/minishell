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

#include "../../include/minishell.h"

int	check_exist_var(char *str)
{
	int	i;
	int	eq;

	eq = (int)(ft_strchr(str, '=') - str);
	if (eq < 0)
		eq = ft_strlen(str);
	else
		eq--;
	i = 0;
	while (__environ[i])
	{
		if (ft_strncmp(__environ[i], str, eq) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	change_var(char *new, int index)
{
	int		i;
	char	*dup_new;

	i = 0;
	if (!ft_strchr(new, '='))
		return ;
	dup_new = ft_strdup(new);
	collect_malloc(dup_new, CHECK);
	collect_malloc(__environ[index], DELETE);
	__environ[index] = dup_new;
}

void	add_var(char ***env, char *new_var)
{
	int		i;
	int		size;
	char	*dup_new;
	char	**new_env;

	i = 0;
	size = size_env(*env);
	dup_new = ft_strdup(new_var);
	collect_malloc(dup_new, ENV_CHECK);
	new_env = malloc(sizeof(char *) * (size + 2));
	collect_malloc(new_env, ENV_CHECK);
	new_env[size] = dup_new;
	new_env[size + 1] = NULL;
}

int	export_add(char **argv)
{
	int		i;
	int		index;

	i = 1;
	while (argv[i])
	{
		if (check_valid_variable(argv[i]))
		{
			index = check_exist_var(argv[i]);
			if (index)
				change_var(argv[i], index);
			else
				add_var(&__environ, argv[i]);
		}
		else
			print_err3("export", argv[i], "not a valid identifier");
		i++;
	}
	return (0);
}
