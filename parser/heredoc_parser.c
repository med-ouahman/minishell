/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:01 by aid-bray          #+#    #+#             */
/*   Updated: 2025/08/14 09:56:37 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static int	eof_exception(char *eof)
{
	ft_printf_fd(STDERR_FILENO, "warning: here-document \
delimited by end-of-file (wanted `%s')\n", eof);
	return (-1);
}

static void	expand_heredoc_var(char **content, char *input, t_info info)
{
	char	*str1;
	char	*var;

	str1 = ft_substr(input, info.start, info.end - info.start);
	collect_malloc(str1, CHECK);
	if (str1[1] == '?')
	{
		var = ft_itoa(access_exit_code(0, READ));
		collect_malloc(var, CHECK);
	}
	else
		var = getenv(str1 + 1);
	if (!var)
		var = "";
	*content = ft_join(*content, 1, var, 0);
	collect_malloc(str1, DELETE);
}

void	parse_latest(char *input, char **content, size_t *i, t_info *info)
{
	char	*tmp;

	tmp = NULL;
	if (check_for_expand(input, *i))
	{
		if (*i != info->start)
		{
			tmp = ft_substr(input, info->start, *i - info->start);
			collect_malloc(tmp, CHECK);
			*content = ft_join(*content, 1, tmp, 1);
			info->start = *i;
		}
		*i = check_for_expand(input, *i);
		info->end = *i;
		expand_heredoc_var(content, input, *info);
		info->start = *i;
	}
	else
		(*i)++;
	if (!input[*i] && info->start < *i)
	{
		tmp = ft_substr(input, info->start, *i - info->start);
		collect_malloc(tmp, CHECK);
		*content = ft_join(*content, 1, tmp, 1);
	}
}

static char	*parser_line(char *input)
{
	char	*content;
	size_t	i;
	t_info	info;

	i = 0;
	ft_memset(&info, 0, sizeof(t_info));
	while (input[i] && !check_for_expand(input, i))
		i++;
	content = ft_substr(input, 0, i);
	collect_malloc(content, CHECK);
	info.start = i;
	while (input[i])
	{
		parse_latest(input, &content, &i, &info);
	}
	return (content);
}

int	write_heredoc(char *line, int writer, char *delimiter, int exp)
{
	char	*content;

	if (!line)
		return (eof_exception(delimiter));
	if (!ft_strcmp(delimiter, line))
	{
		free(line);
		return (-1);
	}
	if (exp || !line[0])
		content = line;
	else
		content = parser_line(line);
	write(writer, content, ft_strlen(content));
	write(writer, "\n", 1);
	if (line != content)
		collect_malloc(content, DELETE);
	free(line);
	return (0);
}
