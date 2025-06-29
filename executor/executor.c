/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:36:37 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/29 11:11:10 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int executor(AST *parse_t)
{
	int	stdio[2];
	char	**pvs;
	t_list	*pipeline;
	t_ast_binary	*bin;

	pvs = split_path();
	if (parse_t->node_type == CMD)
	{
		waitpid(simple_command((t_cmd *)parse_t->data, stdio, pvs), NULL, 0);
		return (0);
	}
	if (parse_t->node_type == PIPE)
	{
		pipeline = create_pipeline(parse_t);
		execute_pipeline(pipeline, pvs);
	}
	if (parse_t->node_type == OR)
	{
		bin = (t_ast_binary *)parse_t;
		if (executor(bin->left))
			return (executor(bin->right));
	}
	if (parse_t->node_type == AND)
	{
		bin = (t_ast_binary *)parse_t;
		if (!executor(bin->left))
			return (executor(bin->right));
	}
	return (0);
}
