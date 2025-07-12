// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   expand_arguments.c                                 :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/07/10 11:29:07 by mouahman          #+#    #+#             */
// /*   Updated: 2025/07/10 11:40:16 by mouahman         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../include/executor.h"

// t_list	*create_list(char **split)
// {
// 	t_list	*list;
// 	t_list	*arg_node;

// 	list = NULL;
// 	while (*split)
// 	{
// 		arg_node = wildcard(*split);
// 		if (!arg_node)
// 			arg_node = ft_lstnew(*split);
// 		ft_lstadd_back(&list, arg_node);
// 		split++;
// 	}
// 	return (list);
// }

// t_list	*expand_arg_node(TOKEN *token)
// {
// 	char	**split;
// 	t_list	*arg_node;
// 	expand(token);

// 	split = NULL;
// 	if (token->split)
// 		split = word_split(token);
// 	if (split)
// 		arg_node = create_list(split);
// 	else
// 		arg_node = wildcard(token->token);
// 	return (arg_node);
// }

// t_list	*expand_arguments(TOKEN *tokens)
// {
// 	t_list	*expanded_args;
// 	t_list	*expanded_node;

// 	expanded_args = NULL;
// 	while (tokens)
// 	{
// 		expanded_node = expand_arg_node(tokens);
// 		ft_lstadd_back(&expanded_args, expanded_node);
// 		tokens = tokens->next;
// 	}
// 	return (expanded_args);
// }
// t_list	*expand_redirections(t_list *redirs)
// {
// 	return (redirs);
// }
