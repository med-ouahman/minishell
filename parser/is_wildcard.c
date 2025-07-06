/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:36:41 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/06 20:19:54 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	is_wildcard(TOKEN *token)
{
	if (token->type != WORD || token->p_quote
		|| !ft_strchr(token->token, '*'))
		return (0);
	return (1);
}
