/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:01 by aid-bray          #+#    #+#             */
/*   Updated: 2025/08/11 09:58:04 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	helper_herdoc(t_list *lst)
{
	static t_list	*lst_cmds = NULL;
	t_list			*cmd_redir;
	t_redir			*redir;

	if (lst)
	{
		lst_cmds = lst;
		return ;
	}
	lst = lst_cmds;
	while (lst)
	{
		cmd_redir = (t_list *)((t_cmd *)lst->content)->redir;
		while (cmd_redir)
		{
			redir = ((t_redir *)cmd_redir->content);
			if (redir->type == RED_HERDOC && redir->heredoc_fd != -1)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			cmd_redir = cmd_redir->next;
		}
		lst = lst->next;
	}
}

static void	update_content(char **content, char *input, t_info info)
{
	char	*str1;
	char	*var;

	str1 = ft_substr(input, info.start, info.end - info.start);
	collect_malloc(str1, CHECK);
	var = getenv(str1);
	if (!var)
		var = "";
	*content = ft_join(*content, 1, var, 0);
	collect_malloc(str1, DELETE);
}

static void	jobe_while(char *input, char **content, size_t*i, t_info *info)
{
	char	*tmp;

	if (check_for_expand(input, (*i)))
	{
		tmp = ft_substr(input, info->start, *i - info->start);
		collect_malloc(tmp, CHECK);
		*content = ft_join(*content, 1, tmp, 1);
		info->start = *i + 1;
		(*i) = check_for_expand(input, (*i));
		info->end = *i;
		update_content(content, input, *info);
		info->start = (*i);
		return ;
	}
	info->end = ++(*i);
}

char	*ft_join(char *str1, int free1, char *str2, int free2)
{
	char	*new;

	if (!str1 && !str2)
		return (NULL);
	if (!str1 && str2)
		str1 = "";
	if (str1 && !str2)
		str2 = "";
	new = ft_strjoin(str1, str2);
	collect_malloc(new, CHECK);
	if (free1 && str1)
		collect_malloc(str1, DELETE);
	if (free2 && str2)
		collect_malloc(str2, DELETE);
	return (new);
}

char	*parser_line(char *input, int _expand)
{
	size_t	i;
	char	*content;
	char	*tmp;
	t_info	info;

	if (_expand || !input[0])
		return (input);
	i = 0;
	ft_memset(&info, 0, sizeof(t_info));
	content = ft_strdup("");
	collect_malloc(content, CHECK);
	while (input[i])
		jobe_while(input, &content, &i, &info);
	if (info.start < info.end)
	{
		tmp = ft_substr(input, info.start, info.end - info.start);
		collect_malloc(tmp, CHECK);
		content = ft_strjoin(content, tmp);
		collect_malloc(content, CHECK);
	}
	return (content);
}
