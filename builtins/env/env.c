/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:23:34 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/19 13:41:14 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"

int	env(int option)
{
	char	**envp;

	envp = __environ;
	while (*envp)
	{
		if (option)
			printf("declare -x ");
		printf("%s\n", *envp);
		envp++;
	}
	return (0);
}
