/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:56:01 by mouahman          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/04 21:19:54 by mouahman         ###   ########.fr       */
=======
/*   Updated: 2025/07/03 17:27:01 by aid-bray         ###   ########.fr       */
>>>>>>> 191da425410b72e73f73348b77e5aea2e344120c
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

void	print_file_error(char *__file, char *__err_msg)
{
<<<<<<< HEAD
	printf("minishell: %s: %s\n", __file, __err_msg);
=======
	ft_printf_fd(2, "minishell: %s: %s\n", file, __err_msg);
>>>>>>> 191da425410b72e73f73348b77e5aea2e344120c
}
