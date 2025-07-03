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

int	pwd(t_cmd *cmd)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 0);
	garbage_collector(cwd, CHECK);
	printf("%s\n", cwd);
	garbage_collector(cwd, FREE);
	return (0);
}
