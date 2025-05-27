/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:49:18 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/26 15:50:08 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

int	is_space(int c)
{
	return (' ' == c || '\t' == c);
}

int	is_quote(int c)
{
	return ('"' == c || '\'' == c);
}

int	is_sep_char(int c)
{
	return ('|' == c
		|| '>' == c
		|| '<' == c
		|| ' ' == c
		|| ')' == c
		|| '(' == c
		|| ' ' == c);
}

int is_sep(char *line, int *i)
{
	char	*seps[] = {"|", ">>", "<<", ">", "<", "&&", "||", "(", ")", NULL};
	int		j;
	int		len;

	j = 0;
	while (seps[j])
	{
		len = ft_strlen(seps[j]);
		if (!ft_strncmp(line, seps[j], len))
		{
			*i = *i + len;
			return (1);
		}
		j++;
	}
	return (0);
}
