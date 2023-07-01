/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:12:55 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/29 11:57:12 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_child(t_pipe *pipex, char *argv[], char *envp[])
{
	pipex->infile = open(argv[1], O_RDONLY);
	error(pipex, pipex->infile);
	error(pipex, dup2(pipex->infile, STDIN_FILENO));
	error(pipex, close(pipex->infile));
	error(pipex, dup2(pipex->pipe[1], STDOUT_FILENO));
	error(pipex, close(pipex->pipe[0]));
	error(pipex, close(pipex->pipe[1]));
	pipex->cmd_paths1 = cmd_exist(pipex, pipex->cmd1[0], envp);
	if (!pipex->cmd_paths1
		|| execve(pipex->cmd_paths1, pipex->cmd1, NULL) == -1)
	{
		write(2, "\n", 1);
		write(2, "command not found\n", 19);
		if (pipex->cmd_paths1)
			free(pipex->cmd_paths1);
		if (pipex->cmd1)
			free_tab(pipex->cmd1);
		if (pipex->cmd2)
			free_tab(pipex->cmd2);
		exit(EXIT_FAILURE);
	}
}

void	second_child(t_pipe *pipex, char *argv[], char *envp[])
{
	pipex->outfile = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	error(pipex, pipex->outfile);
	error(pipex, dup2(pipex->outfile, STDOUT_FILENO));
	error(pipex, close(pipex->outfile));
	error(pipex, dup2(pipex->pipe[0], STDIN_FILENO));
	error(pipex, close(pipex->pipe[0]));
	error(pipex, close(pipex->pipe[1]));
	pipex->cmd_paths2 = cmd_exist(pipex, pipex->cmd2[0], envp);
	if (!pipex->cmd_paths2
		|| execve(pipex->cmd_paths2, pipex->cmd2, NULL) == -1)
	{
		write(2, "command not found\n", 19);
		if (pipex->cmd_paths2)
			free(pipex->cmd_paths2);
		if (pipex->cmd2)
			free_tab(pipex->cmd2);
		if (pipex->cmd1)
			free_tab(pipex->cmd1);
		exit(EXIT_FAILURE);
	}
}

void	parent(t_pipe *pipex)
{
	int	i;

	error(pipex, close(pipex->pipe[0]));
	error(pipex, close(pipex->pipe[1]));
	error(pipex, waitpid(pipex->pid1, &pipex->status, 0));
	error(pipex, waitpid(pipex->pid2, &pipex->status, 0));
	i = -1;
	while (pipex->cmd1[++i])
		free(pipex->cmd1[i]);
	free(pipex->cmd1);
	i = -1;
	while (pipex->cmd2[++i])
		free(pipex->cmd2[i]);
	free(pipex->cmd2);
}
