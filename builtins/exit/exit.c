/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:07:58 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/04 15:54:24 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	check_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (ft_isdigit(arg[i]))
		i++;
	if (!arg[i])
		return (0);
	return (1);
}

static int	exit_nbr(const char *nptr)
{
	int		i;
	int		sign;
	size_t	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		nb = nb * 10 + (nptr[i] - 48);
		if (nb > (size_t)LONG_MAX + 1)
			return (-1);
		i++;
	}
	nb = (nb * sign) % 256;
	return (nb);
}

static void	exit_2(t_cmd *cmd)
{
	if (check_arg(cmd->args->next->content))
	{
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			(char *)cmd->args->next->content);
		exit(2);
	}
	else
		ft_printf_fd(2, "minishell: exit: too many arguments\n",
			(char *)cmd->args->next->content);
}

int	exit_(t_cmd *cmd)
{
	int	exit_status;

	ft_printf_fd(1, "exit\n");
	exit_status = 2;
	if (!cmd->args->next)
		exit (EXIT_SUCCESS);
	if (!cmd->args->next->next)
	{
		exit_status = exit_nbr((const char *)cmd->args->next->content);
		if (check_arg(cmd->args->next->content))
			ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
				(char *)cmd->args->next->content);
		else if (exit_status == -1)
		{
			ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
				(char *)cmd->args->next->content);
			exit_status = 2;
		}
		exit(exit_status);
	}
	exit_2(cmd);
	return (0);
}
