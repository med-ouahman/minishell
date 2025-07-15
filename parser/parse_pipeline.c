/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:08:45 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/05 15:47:31 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_list *parse_pipeline(TOKEN **tokens)
{
	TOKEN		*token;
	t_list		*left;
	t_list		*right;

	if (!peek(*tokens) || error(0, READ))
		return (NULL);
	left = parse_command(tokens);
	if (!left)
		return (NULL);
	token = peek(*tokens);
	while (token && token->type == PIPE)
	{
		consume(tokens);
		right = parse_command(tokens);
		if (error(0, READ))
			return (NULL);
		if (!right)
		{
			syntax_error(PIPE, peek(*tokens));
			return (NULL);
		}
		ft_lstadd_back(&left, right);
		token = peek(*tokens);
	}
	return (left);
}
