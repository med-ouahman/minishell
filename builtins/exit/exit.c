/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:07:58 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/05 17:13:29 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (ft_isdigit(arg[i]))
		i++;
	while (ft_isspace(arg[i]))
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
	if (!nptr[i])
		return (-1);
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		sign = 0 - (nptr[i] == '-');
		i += (sign == -1);
	}
	while (ft_isdigit(nptr[i]))
	{
		nb = nb * 10 + (nptr[i] - 48);
		if (nb > (size_t)LONG_MAX + (sign == -1))
			return (-1);
		i++;
	}
	return ((nb * sign) % 256);
}

static int	exit_2(char **args, int *stdio)
{
	char	*arg;

	arg = args[1];
	if (check_arg(arg))
	{
		close_stdio(stdio);
		print_err3("exit", arg, "numeric argument required");
		cleanup(2);
	}
	else
	{
		print_err2("exit", "too may arguments");
		return (1);
	}
	return (0);
}

int	exit_(char **args, int *stdio)
{
	int		exit_status;

	exit_status = 2;
	if (args[1] == NULL)
	{
		close_stdio(stdio);
		cleanup(access_exit_code(0, READ));
	}
	if (!args[2])
	{
		exit_status = exit_nbr(args[1]);
		if (check_arg(args[1]))
			print_err3("exit", args[1], "numeric argument required");
		else if (exit_status == -1)
		{
			print_err3("exit", args[1], "numeric argument required");
			exit_status = 2;
		}
		close_stdio(stdio);
		cleanup(exit_status);
	}
	return (exit_2(args, stdio));
}
