/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:36:37 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/26 11:38:04 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int executor(t_list *exec_list)
{
	char	**pvs;
	t_list	*curr;
	t_cmd	*cmd;
	int		**pipes;
	int		stdio[2];
	pid_t	*pids;
	int		i;
	int		lsize;
	
	pvs = split_path(__environ);
	curr = exec_list;
	lsize = ft_lstsize(exec_list);
	pipes = create_pipes(lsize - 1);
	pids = malloc(lsize * sizeof(pid_t));
	garbage_collector(pids, ALLOC);
	i = 0;
	while (curr)
	{
		cmd = (t_cmd *)curr->content;
		set_stdio(cmd, stdio);
		if (STDIN_FILENO == stdio[0] && curr > exec_list)
		{
			stdio[0] = pipes[i - 1][0];
		}
		if (STDOUT_FILENO == stdio[1] && curr->next)
		{
			stdio[1] = pipes[i][1];
		}
		pids[i] = simple_command(cmd, stdio, pvs);
		curr = curr->next;
		i++;
	}
	close_pipes(pipes);
	return (wait_children(pids, lsize));
}
