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
	char	*line;
	LIST	*token_list;
	
	line = readline("$ ");
	while (line)
	{
		add_history(line);
		token_list = create_token_list(line);
		print_token_list(token_list);
		expand(token_list);
		free(line);
		line = readline("$ ");
		if (NULL == line)
			return (1);
	}
}
