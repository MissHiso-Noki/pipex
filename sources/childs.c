/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:12:55 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/22 11:37:01 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_child(t_pipe pipex, char *envp[])
{
	error(dup2(pipex.infile, STDIN_FILENO));
	error(dup2(pipex.pipe[1], STDOUT_FILENO));
	error(close(pipex.pipe[0]));
	error(close(pipex.pipe[1]));
	pipex.cmd_paths1 = cmd_exist(pipex.cmd1[0], envp);
	cmd_not_found(pipex.cmd_paths1, pipex.cmd1);
	error(execve(pipex.cmd_paths1, pipex.cmd1, NULL));
}

void	second_child(t_pipe pipex, char *envp[])
{
	error(dup2(pipex.pipe[0], STDIN_FILENO));
	error(dup2(pipex.outfile, STDOUT_FILENO));
	error(close(pipex.pipe[0]));
	error(close(pipex.pipe[1]));
	pipex.cmd_paths2 = cmd_exist(pipex.cmd2[0], envp);
	cmd_not_found(pipex.cmd_paths2, pipex.cmd2);
	error(execve(pipex.cmd_paths2, pipex.cmd2, NULL));
}

void	parent(t_pipe pipex)
{
	int	i;

	error(close(pipex.pipe[0]));
	error(close(pipex.pipe[1]));
	error(close(pipex.infile));
	error(close(pipex.outfile));
	error(waitpid(pipex.pid1, &pipex.status, 0));
	error(waitpid(pipex.pid2, &pipex.status, 0));
	i = -1;
	while (pipex.cmd1[++i])
		free(pipex.cmd1[i]);
	free(pipex.cmd1);
	i = -1;
	while (pipex.cmd2[++i])
		free(pipex.cmd2[i]);
	free(pipex.cmd2);
}
