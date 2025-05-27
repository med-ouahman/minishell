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

#include "../includes/minishell.h"

int	main(void)
{
	char			*line;
	t_parse_tree	*parse_t=NULL;

	line = "";
	while (line)
	{
		signal(SIGINT, signal_handler);
		line = readline("$ ");
		if (!ft_strcmp("clear", line))
			system("clear");
		add_history(line);
		if (NULL == line)
			return (1);
		parse_t = parser(line);
		print_tree(parse_t, 1);
	}
}
