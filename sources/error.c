/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:12:12 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/29 11:40:47 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	msg_error(char *error)
{
	write(1, error, ft_strlen(error));
	return (1);
}

void	error(t_pipe *pipex, int ret)
{
	if (ret == -1)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		if (pipex->pipe[0])
			close(pipex->pipe[0]);
		if (pipex->pipe[1])
			close(pipex->pipe[1]);
		if (pipex->cmd1)
			free_tab(pipex->cmd1);
		if (pipex->cmd2)
			free_tab(pipex->cmd2);
		exit(1);
	}
}

void	child_error(t_pipe *pipex, char *cmd, char **paths)
{
	char	*msg_errr;

	msg_errr = ft_strjoin(cmd, ": command not found\n");
	if (msg_errr)
	{
		write(2, msg_errr, ft_strlen(msg_errr));
		free(msg_errr);
	}
	if (paths)
	{
		free_tab(paths);
	}
	if (pipex->cmd1)
		free_tab(pipex->cmd1);
	if (pipex->cmd2)
		free_tab(pipex->cmd2);
	exit (EXIT_FAILURE);
}
