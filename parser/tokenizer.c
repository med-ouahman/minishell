/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:58:42 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/29 10:56:56 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"

int	add_regular(TOKEN **tokens, char *line, t_info info, int *ii);

void	add_node(TOKEN **list, TOKEN *node)
{
	TOKEN	*last;

	if (NULL == *list)
	{
		*list = node;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = node;
}

int	token_type(char *s, int type)
{
	if (type == WORD)
		return (type);
	if (!ft_strcmp(s, "|"))
		return (PIPE);
	if (!ft_strcmp(s, ">"))
		return (REDOUT);
	if (!ft_strcmp(s, "<"))
		return (REDIN);
	if (!ft_strcmp(s, ">>"))
		return (REDOUTAPP);
	if (!ft_strcmp(s, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(s, "||"))
		return (OR);
	if (!ft_strcmp(s, "&&"))
		return (AND);
	if (!ft_strcmp(s, "("))
		return (OPENPAR);
	if (!ft_strcmp(s, ")"))
		return (CLOSEPAR);
	if (!ft_strcmp(s, "*"))
		return (WILDCARD);
	return (-1);
}

int	add_token(TOKEN **list, char *line, t_info info)
{
	TOKEN	*token;
	
	if (info.start == info.end)
		return (0);
	token = malloc(sizeof *token);
	if (NULL == token)
		return (-1);
	token->type = info.type;
	token->p_quote = info.quote;
	token->token = ft_substr(line, info.start, info.end - info.start);
	token->start = info.start == 0 ? line[info.start]: line[info.start - 1];
	token->end = line[info.end];
	token->type = token_type(token->token, token->type);
	token->join_with = NULL;
	token->next = NULL;
	add_node(list, token);
	return (0);
}

int		add_quoted_token(TOKEN **tokens, char *line, t_info info, int *ii)
{
	int	i;

	i = *ii;
	info.quote = line[i++];
	info.start = i;
	while (line[i] != info.quote && line[i])
		i++;
	if (!line[i])
		return (panic("minishell: parse error: unclosed quote\n", -1));
	info.end = i;
	info.type = WORD;
	add_token(tokens, line, info);
	if (line[i] == info.quote)
		i++;
	*ii = i;
	return (i);
}

int	add_operator(TOKEN **tokens, char *line, t_info info, int *ii)
{
	
	info.start = *ii;
	if (0 == is_sep(line + (*ii), ii))
	{
		info.type = WORD;
		info.start = (*ii)++;
		while (!is_sep_char(line[*ii]) && !is_space(line[*ii]) && !is_quote(line[*ii]) && line[*ii])
			(*ii)++;
		info.end = *ii;
		add_token(tokens, line, info);
		return (0);
	}
	info.end = *ii;
	info.type = OPERATOR;
	info.quote = 0;
	add_token(tokens, line, info);
	return (*ii);
}

int	add_regular(TOKEN **tokens, char *line, t_info info, int *ii)
{
	int	i;

	i = *ii;
	while (is_space(line[i]))
		i++;
	info.start = i;
	while (!is_sep_char(line[i]) && !is_space(line[i]) && !is_quote(line[i]) && line[i])
		i++;
	info.end = i;
	info.type = WORD;
	info.quote = 0;
	add_token(tokens, line, info);
	*ii = i;
	return (i);
}

TOKEN	*tokenizer(char *line)
{
	TOKEN	*tokens;
	int	i;
	t_info	info;
	
	i = 0;
	tokens = NULL;
	info.quote = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
		{
			if (-1 == add_quoted_token(&tokens, line, info, &i))
				return (NULL);
		}
		else if (is_sep_char(line[i]))
			add_operator(&tokens, line, info, &i);
		else
			add_regular(&tokens, line, info, &i);
	}
	join_tokens(&tokens);
	return (tokens);
}
