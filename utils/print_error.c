/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:36:20 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/05 14:44:20 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

void	print_file_error(char *__file, char *__err_msg)
{
	ft_printf_fd(2, "minishell: %s: %s\n", __file, __err_msg);
}

void	print_file_error2(char *filename, char *_path, char *__err_msg)
{
	ft_printf_fd(2, "%s: %s: %s\n", filename, _path, __err_msg);
}
