/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:29:28 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/23 09:30:12 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_list  *get_args(TOKEN **tokens)
{
	TOKEN    *curr;
	char    **split;
	t_list  *args;
	t_list  *arg_node;

	args = NULL;
	curr = peek(*tokens);
	split = NULL;
	while (curr && curr->type == WORD)
	{
		expand(curr, 0);
		if (curr->split)
		{
			split = word_split(curr, " \t\n\v\r\f");
			garbage_collector(split, ALLOC);
		}
		if (split)
			while (*split)
			{
				arg_node = ft_lstnew(*split);
				ft_lstadd_back(&args, arg_node);
				split++;
			}
		else
		{
			arg_node = ft_lstnew(curr->token);
			ft_lstadd_back(&args, arg_node);
		}
		consume(tokens);
		curr = peek(*tokens);
	}
	return (args);
}

t_cmd   *build_command(TOKEN **tokens)
{
	t_cmd   *cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->args = get_args(tokens);
	cmd->redirs = get_redirs(tokens);
	if (cmd->args)
		cmd->is_buitlin = is_builtin(cmd->args->content);
	return (cmd);
}

AST *parse_command(TOKEN **tokens)
{
	AST     *command;
	t_cmd   *cmd;

	if (*tokens == NULL)
		return (NULL);
	command = malloc(sizeof(*command));
	garbage_collector(command, ALLOC);
	if (!command)
	   return (NUlL);
	command->node_type = CMD;
	cmd = build_command(tokens);
	if (!cmd)
		return (NUlL);
	command->data = cmd;
	return (command);
}
