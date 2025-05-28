/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_properties.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:14:50 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/28 11:15:45 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	is_starting(int c)
{
	return (ft_isalpha(c) || '_' == c);
}

int	is_subsequent(int c)
{
	return (is_starting(c) || ft_isdigit(c));
}

int	invalid_var_char(int c)
{
	return (!is_starting(c) && !is_subsequent(c));
}
