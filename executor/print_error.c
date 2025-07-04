/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:56:01 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/03 17:27:01 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

void	print_file_error(char *file, char *__err_msg)
{
	ft_printf_fd(2, "minishell: %s: %s\n", file, __err_msg);
}
