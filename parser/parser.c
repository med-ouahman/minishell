/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:17:09 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/06 11:33:26 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_list *parser(TOKEN *tokens)
{
	t_list *pipeline;

	error(0, WRITE);
	pipeline = parse_pipeline(&tokens);
	if (error(0, READ))
		return (NULL);
	if (tokens != NULL)
	{
		syntax_error(-1, peek(tokens));
		return (NULL);
	}
	return (pipeline);
}
