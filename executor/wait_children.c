/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:16:38 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/08 12:25:14 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

static void	if_signaled(int status, int *first)
{
	if (WTERMSIG(status) == SIGINT && *first == 0)
	{
		*first = 1;
		printf("\n");
	}
	else if (WTERMSIG(status) == SIGQUIT && *first == 0)
	{
		*first = 1;
		printf("Quit\n");
	}
}

int	wait_children(pid_t *pids, t_uint num_children)
{
	int		first;
	int		status;
	t_uint	i;

	i = 0;
	first = 0;
	status = 0;
	while (i < num_children)
	{
		if (-1 != pids[i])
		{
			waitpid(pids[i], &status, 0);
			if (WIFSIGNALED(status))
				if_signaled(status, &first);
		}
		i++;
	}
	status = exit_code(status);
	handle_signals();
	return (status);
}

/*
#include <sys/resource.h>

void	get_child_resource_usage(pid_t pid)
{
	struct rusage	r;
	
	wait4(pid, NULL, 0, &r);
	printf("user CPU time: seconds: %ld - micro: %ld\n",
	r.ru_utime.tv_sec, r.ru_utime.tv_usec);
	printf("system CPU time: seconds: %ld - micor: %ld\n",
	r.ru_stime.tv_sec, r.ru_stime.tv_usec);
	printf("maximum resident set size: %ld\n", r.ru_maxrss);
	printf("integral shared memory size: %ld\n", r.ru_ixrss);
	printf("integral unshared data size: %ld\n", r.ru_idrss);
	printf("integral unshared stack size :%ld\n", r.ru_isrss);
	printf("page reclaims (soft page faults): %ld\n", r.ru_minflt);
	printf("page fault (hard): %ld\n", r.ru_majflt);
	printf("swaps: %ld\n", r.ru_nswap);
	printf("block input operations: %ld\n", r.ru_inblock);
	printf("block output operations: %ld\n", r.ru_oublock);
	printf("IPC messages sent: %ld\n", r.ru_msgsnd);
	printf("IPC messages received: %ld\n", r.ru_msgrcv);
	printf("signals received: %ld\n", r.ru_nsignals);
	printf("voluntary context switches: %ld\n", r.ru_nvcsw);
	printf("involuntary context switches: %ld\n", r.ru_nivcsw);
}
*/