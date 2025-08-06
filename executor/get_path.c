/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 21:21:18 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/06 10:40:51 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

char	*getpath(int init)
{
	static char	*path;

	if (!init)
		path = getenv("PATH");
	return (path);
}

static char	*reset(char *old_val, int *offset, int *null_pos)
{
	char	*path;

	path = getpath(1);
	if (path)
		path[*null_pos] = *old_val;
	*old_val = 0;
	*offset = 0;
	*null_pos = 0;
	return (0);
}

char	*get_next_path(char *path, int r)
{
	static char	old_val; 
	static int	offset;
	static int	null_pos;
	int			start;
	int			old_offset;

	if (offset < 0 || r || !path)
		return (reset(&old_val, &offset, &null_pos));
	start = offset;
	old_offset = offset;
	if (old_val)
		path[null_pos] = old_val;
	while (path[start] && path[start] != ':')
		start++;
	if (path[start] == 0)
	{
		path += offset;
		offset = -1;
		return (path);
	}
	null_pos = start++;
	old_val = path[null_pos];
	path[null_pos] = 0;
	offset = start;
	return (path + old_offset);
}
