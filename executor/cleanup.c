/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:02:04 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/11 06:27:59 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	cleanup(int code)
{
	rl_clear_history();
	collect_malloc(NULL, DESTROY);
	exit(code);
	return (code);
}
