/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:28:48 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/27 13:30:02 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/signal_handler.h"

int	new_prompt(char **line, char *prompt)
{
	*line = readline(prompt);
	return (0);
}
