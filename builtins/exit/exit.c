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

#include "../../include/minishell.h"

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

static void	exit_2(char **args)
{
	char	*arg;

	arg = args[1];
	if (check_arg(arg))
	{
		print_file_error2("exit", arg, "numeric argument required");
		exit(2);
	}
	else
		print_file_error("exit", "too may arguments");
}

int	exit_(char **args)
{
	int		exit_status;
	char	*arg;

	ft_printf_fd(2, "exit\n");
	exit_status = 2;
	if (!args[1])
		exit (EXIT_SUCCESS);
	if (!args[2])
	{
		arg = args[1];
		exit_status = exit_nbr(arg);
		if (check_arg(arg))
			print_file_error2("exit", arg, "numeric argument required");
		else if (exit_status == -1)
		{
			print_file_error2("exit", arg, "numeric argument required");
			exit_status = 2;
		}
		exit(exit_status);
	}
	exit_2(args);
	return (0);
}
