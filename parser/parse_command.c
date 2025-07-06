/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:29:28 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/06 11:43:26 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	add_splitted_argument(t_list **args, TOKEN *token)
{
	char	**split;
	t_list	*arg_node;

	split = word_split(token);
	while (*split && **split)
	{
		arg_node = ft_lstnew(*split);
		ft_lstadd_back(args, arg_node);
		split++;
	}
}

t_list  *build_command_args(TOKEN **tokens)
{
	TOKEN    *curr;
	t_list  *args;
	t_list  *arg_node;

	args = NULL;
	curr = peek(*tokens);
	while (curr && (curr->type == WORD))
	{
		expand(curr);
		quote_removal(curr);
		if (curr->split)
			add_splitted_argument(&args, curr);
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
	TOKEN	*token;

	cmd = my_alloc(sizeof *cmd);
	cmd->args = build_command_args(tokens);
	cmd->redirs = get_redirs(tokens);
	if (error(0, READ))
		return (NULL);
	token = peek(*tokens);
	while (token && token->type == WORD)
	{
		ft_lstadd_back(&cmd->args, build_command_args(tokens));
		ft_lstadd_back(&cmd->redirs, get_redirs(tokens));
		token = peek(*tokens);
	}
	if (cmd->args)
		cmd->is_buitlin = is_builtin(cmd->args->content);
	return (cmd);
}

AST *parse_command(TOKEN **tokens)
{
	TOKEN	*token;
	AST     *command;
	t_cmd   *cmd;

	if (error(0, READ))
		return (NULL);
	token = peek(*tokens);
	if (!tokens || (token->type != WORD && token->type != WILDCARD
		&& !is_redirection(token->type)))
	{
		error(1, WRITE);
		syntax_error(CMD, token);
		return (NULL);
	}
	command = malloc(sizeof *command);
	garbage_collector(command, COLLECT);
	if (!command)
	   return (NUlL);
	command->node_type = CMD;
	cmd = build_command(tokens);
	if (!cmd)
		return (NUlL);
	command->data = cmd;
	return (command);
}
