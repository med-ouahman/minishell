/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:12:02 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/29 10:58:05 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	execute_pipeline(t_list *pipeline, char **pvs)
{
    int         stdio[2];
    int      size;
    t_pipefd    *pipes;
    int         i;
    pid_t       *pids;
    t_cmd       *cmd;

    size = ft_lstsize(pipeline);
    pipes = create_pipes(size - 1);
    pids = malloc(size * sizeof *pids);
    garbage_collector(pids, ALLOC);
    i = 0;
    while (pipeline)
    {
        cmd = (t_cmd *)pipeline->content;
        set_stdio(cmd, stdio);
        if (stdio[0] == STDIN_FILENO && i > 0)
        {
            stdio[0] = pipes[i - 1].pipefds[0];
        }
        if (stdio[1] == STDOUT_FILENO && (i < size - 1))
        {
            stdio[1] = pipes[i].pipefds[1];
        }
        pids[i] = simple_command(cmd, stdio, pvs);
        pipeline = pipeline->next;
        i++;
    }
    close_pipes(pipes, size - 1);
    wait_children(pids, size);
    return (0);
}
