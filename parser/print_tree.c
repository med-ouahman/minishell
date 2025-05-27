/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:58:39 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/23 17:03:54 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

void	print_tree(t_parse_tree *tree, int dir)
{
	while (tree)
	{
		printf("%s\n", tree->token->token);
		if (dir)
			tree = tree->left;
		else
			tree = tree->right;
	}
}
