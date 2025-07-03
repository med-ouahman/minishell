/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:56:01 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/01 09:52:38 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

void	print_file_error(char *file, char *__err_msg)
{
	printf("minishell: %s: %s\n", file, __err_msg);
}
