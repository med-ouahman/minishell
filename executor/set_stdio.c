/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_stdio.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:48:34 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/27 20:58:14 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	redirection_flags(int redir_type)
{
	if (redir_type == REDIN || redir_type == HEREDOC)
		return (O_RDONLY);
	if (redir_type == REDOUT)
		return (O_CREAT | O_WRONLY | O_TRUNC);
	if (redir_type == REDOUTAPP)
		return (O_CREAT | O_WRONLY | O_APPEND);
	return (-1);
}

int	open_redin(char *filename)
{
	int	fd;

	if (access(filename, F_OK))
	{
		printf("minishell: %s: No such file or directory\n", filename);
		return (-1);
	}
	else if (access(filename, W_OK))
	{
		printf("minishell: %s: Permission denied\n", filename);
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("minishell: %s: Error opening file\n", filename);
		return (-1);
	}
	return (fd);
}

int	open_redout(char *filename, int mode)
{
	int	fd;

	if (!access(filename, F_OK) && access(filename, W_OK))
	{
		printf("minishell: %s: Permission denied\n", filename);
		return (-1);
	}
	fd = open(filename, mode, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: Error opening file\n", filename);
		return (-1);
	}
	return (fd);
}

int	set_stdio(t_cmd *cmd, int *stdio)
{
	t_redir	*redir;
	t_list	*redirs;
	int		fd;

	stdio[STDIN_FILENO] = STDIN_FILENO;
	stdio[STDOUT_FILENO] = STDOUT_FILENO;
	if (cmd->redirs == NULL)
		return (0);
	redirs = cmd->redirs;
	while (redirs)
	{
		redir = (t_redir *)cmd->redirs->content;
		if (redir->type == REDIN || redir->type == HEREDOC)
		{
			fd = open_redin(redir->target);
			if (fd < 0)
				return (-1);
			stdio[0] = fd;
			if (redirs->next)
				close(fd);
		}
		else
		{
			fd = open_redout(redir->target, redirection_flags(redir->type));
			if (fd < 0)
				return (-1);
			stdio[1] = fd;
			if (redirs->next)
				close(fd);
		}
		redirs = redirs->next;
	}
	return (0);
}
