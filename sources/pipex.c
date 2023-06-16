/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:36:48 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/16 14:04:53 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
	{
		envp++;
	}
	return (*envp + 5);
}

void	close_pipes(t_pipe *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
}

// void	open_files(t_pipe pipex, int argc, char *argv[])
// {

// }

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	pipex;

	if (argc != 5)
	{
		msg(ERR_INPUT);
		exit(EXIT_FAILURE);
	}
//	open_files(pipex, argc, argv);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		msg_perror(ERR_INFILE);
	pipex.outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (pipex.outfile < 0)
		msg_perror(ERR_OUTFILE);
	if (pipe(pipex.pipe) < 0)
	{
		close(pipex.infile);
		close(pipex.outfile);
		msg_perror(ERR_PIPE);
	}
	pipex.path = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.path, ':');
	first_child(pipex, argv, envp);
	second_child(pipex, argv, envp);
	close_pipes(&pipex);
	close(pipex.infile);
	close(pipex.outfile);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	parent_free(&pipex);
	return (0);
}
