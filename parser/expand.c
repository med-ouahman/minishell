/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:50:54 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/06 11:42:34 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"

int	add_raw_token(t_list **var_list, char *str, int start, int end)
{
	char	*s;
	t_list	*node;

	if (start == end)
		return (0);
	s = ft_substr(str, start, end - start);
	if (NULL == s)
	{
		ft_lstclear(var_list, free);
		return (-1);
	}
	node = ft_lstnew(s);
	if (NULL == node)
	{
		free(s);
		ft_lstclear(var_list, free);
		return (-1);
	}
	ft_lstadd_back(var_list, node);
	return (0);
}

int	expand_token(t_list **var_list, char *str, int start, int end)
{
	char	*key;
	char	*value;
	t_list	*node;

	if (start == end)
		return (0);
	key = ft_substr(str, start, end - start);
	value = getenv(key);
	free(key);
	if (NULL == value)
		node = ft_lstnew(ft_strdup(""));
	else
	{
		value = ft_strdup(value);
		node = ft_lstnew(value);
	}
	if (NULL == node)
	{
		free(value);
		ft_lstclear(var_list, free);
		return (-1);
	}
	ft_lstadd_back(var_list, node);
	return (0);
}

char	*expand_var_list(t_list *var_list)
{
	char	*result;
	size_t	lsize;

	lsize = get_lsize(var_list) + 1;
	result = malloc(lsize * sizeof(char));
	if (NULL == result)
		return (NULL);
	result[0] = 0;
	copy_list(result, var_list, lsize);
	return (result);
}

t_list	*get_var_list(char *str)
{
	t_list	*var_list;
	int		i;
	int		j;
	
	var_list = NULL;
	i = 0;
	while (str[i])
	{
		j = i;
		while (str[i] && str[i] != '$')
			i++;
		add_raw_token(&var_list, str, j, i);
		if (!str[i])
			break ;
		j = i++;
		if (!is_starting(str[i]))
		{
			if ('?' == str[i])
			{
				add_exit_code(&var_list, access_exit_code(0, READ));
				i++;
			}
			else
			{
				while (str[i] && '$' != str[i] && !is_starting(str[i]))
					i++;
				add_raw_token(&var_list, str, j, i);
			}
			continue ;
		}
		j = i++;
		while (is_subsequent(str[i]))
			i++;
		expand_token(&var_list, str, j, i);
	}
	return (var_list);
}

t_list *expand(TOKEN *token)
{
	char	*tmp;
	t_list	*var_list;
	
	if (token->p_quote)
		token->split = 0;
	else
		token->split = is_splittable(token->token);
	var_list = get_var_list(token->token);
	if (!var_list)
		return (NULL);
	tmp = token->token;
	token->token = expand_var_list(var_list);
	if (token->split)
		token->split = has_spaces(token->token);
	free(tmp);
	ft_lstclear(&var_list, free);
	return (word_split(token));
}

