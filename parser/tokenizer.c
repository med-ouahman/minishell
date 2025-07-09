/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:58:42 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/05 16:25:37 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"

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
	return (-1);
}

int	add_token(TOKEN **list, char *line, t_info info)
{
	TOKEN	*token;
	
	token = my_alloc(sizeof *token, COLLECT);
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

int	add_operator(TOKEN **tokens, char *line, int *ii)
{
	t_info	info;

	info.start = *ii;
	if (0 == is_sep(line + (*ii), ii))
	{
		info.type = WORD;
		info.start = (*ii)++;
		while (!is_sep_char(line[*ii])
			&& !is_space(line[*ii]) && !is_quote(line[*ii]) && line[*ii])
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

int	add_regular(TOKEN **tokens, char *line, int *ii)
{
	int		open_q;
	int		close_q;
	int		i;
	t_info	info;

	open_q = 0;
	close_q = 0;
	i = *ii;
	while (is_space(line[i]))
		i++;
	info.start = i;
	while (!is_sep_char(line[i]) && !is_space(line[i]) && line[i])
	{
		if (open_q == line[i])
			close_q = line[i];
		if (!open_q && is_quote(line[i]))
		{
			open_q = line[i++];
			while (line[i] && line[i] != open_q)
				i++;
			continue ;
		}
		if (close_q == open_q)
		{
			info.quote = open_q;
			open_q = close_q = 0;
		}
		i++;
	}
	if (open_q != close_q)
		return (panic("minishell: parse error: unclosed quote\n", -1));
	info.end = i;
	info.type = WORD;
	add_token(tokens, line, info);
	*ii = i;
	return (i);
}

TOKEN	*tokenizer(char *line)
{
	TOKEN	*tokens;
	int	i;
	
	i = 0;
	tokens = NULL;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		if (is_sep_char(line[i]))
		{
			if (add_operator(&tokens, line, &i) < 0)
				return (NULL);
		}
		else
		{
			if (0 > add_regular(&tokens, line, &i))
				return (NULL);
		}
	}
	return (tokens);
}
