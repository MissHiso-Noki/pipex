/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:12:55 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/16 13:52:07 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
		{
			msg_perror("command not found");
		}
		command = ft_strjoin(tmp, cmd);
		if (!command)
		{
			free(tmp);
			msg_perror("command not found");
		}
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	first_child(t_pipe pipex, char *argv[], char *envp[])
{
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
	{
		dup2(pipex.pipe[1], 1);
		dup2(pipex.infile, 0);
		pipex.cmd_args = ft_split(argv[2], ' ');
		if (!pipex.cmd_args)
		{
			child_free(&pipex);
			msg(ERR_CMD);
		}
		pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
		if (!pipex.cmd)
		{
			close_pipes(&pipex);
			close(pipex.infile);
			child_free(&pipex);
			msg(ERR_CMD);
		}
		close_pipes(&pipex);
		close(pipex.infile);
		execve(pipex.cmd, pipex.cmd_args, envp);
	}
}

void	second_child(t_pipe pipex, char *argv[], char *envp[])
{
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
	{
		dup2(pipex.pipe[0], 0);
		dup2(pipex.outfile, 1);
		pipex.cmd_args = ft_split(argv[3], ' ');
		pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
		if (!pipex.cmd)
		{
			close_pipes(&pipex);
			close(pipex.outfile);
			child_free(&pipex);
			msg(ERR_CMD);
		}
		close_pipes(&pipex);
		close(pipex.outfile);
		execve(pipex.cmd, pipex.cmd_args, envp);
	}
}
