/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.1337.ma>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:19:14 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/19 13:41:09 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char			*line;
	t_parse_tree	*parse_t;

	line = "";
	while (line)
	{
		line = readline("$ ");
		if (NULL == line)
		{
			clear_history();
			exit(0);
		}
		add_history(line);
		if (!ft_strncmp(line, "clear", 5))
			system("clear");
		parse_t = parser(line);
		free(line);
		expand(parse_t);
		print_tree(parse_t, 1);
	}
}
