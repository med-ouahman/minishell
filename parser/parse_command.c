/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:29:28 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/06 14:28:57 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

TOKEN  *build_command_args(TOKEN **tokens)
{
	TOKEN    *curr;
	TOKEN  	*args;
	TOKEN	*next;

	args = NULL;
	curr = peek(*tokens);
	while (curr && curr->type == WORD)
	{
		next = consume(tokens);
		curr->next = NULL;
		add_token_back(&args, curr);
		curr = peek(*tokens);
	}
	return (args);
}

t_cmd   *build_command(TOKEN **tokens)
{
	t_cmd   *cmd;
	TOKEN	*token;

	cmd = my_alloc(sizeof *cmd, COLLECT);
	cmd->args = build_command_args(tokens);
	cmd->redirs = get_redirs(tokens);
	if (error(0, READ))
		return (NULL);
	token = peek(*tokens);
	while (token && token->type == WORD)
	{
		add_token_back(&cmd->args, build_command_args(tokens));
		ft_lstadd_back(&cmd->redirs, get_redirs(tokens));
		token = peek(*tokens);
	}
	if (cmd->args)
		cmd->is_buitlin = is_builtin(cmd->args->token);
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
