/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:09 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/31 06:50:31 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	free_list_token(t_token *token)
{
	t_token	*t;

	while (token)
	{
		t = token->next;
		if (token)
			collect_malloc(token, DELETE);
		token = t;
	}
}

t_list	*parser(char *input)
{
	t_token	*token;
	t_list	*cmd;
	int		valid;
	
	token = get_tokens(input);
	if (!token)
		return (NULL);
	valid = check_valid_input(token);
	if (valid)
		return (NULL);
	cmd = set_cmd(token);
	if (!cmd)
		return (NULL);
	free_list_token(token);
	expand(cmd);
	return (cmd);
}
