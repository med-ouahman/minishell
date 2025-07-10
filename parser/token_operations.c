/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:40:09 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/19 11:40:34 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

TOKEN	*peek(TOKEN *tokens)
{
	if (NULL == tokens)
		return (NULL);
	return (tokens);
}

void	consume(TOKEN **tokens)
{
	if (*tokens == NULL)
		return ;
	*tokens = (*tokens)->next;
}
