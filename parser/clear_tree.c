/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:35:45 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/29 14:39:12 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	clear_tree(t_parse_tree *tree)
{
	t_parse_tree	*left;
	t_parse_tree	*right;

	if (NULL == tree)
		return (0);
	left = tree->left;
	right = tree->right;
	free(tree);
	clear_tree(left);
	clear_tree(right);
	return (0);
}
