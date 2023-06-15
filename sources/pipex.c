/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:36:48 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/15 15:51:35 by ccoste           ###   ########.fr       */
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

void	error_in(int argc)
{
	if (argc != 5)
	{
		msg(ERR_INPUT);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	pipex;


	error_in(argc);
	printf("%d\n", argc);
	pipex.infile = open(argv[1], O_RDONLY);
	if (argv[1] == NULL)
		msg_perror(ERR_INFILE);
	pipex.outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (argv[argc - 1] == NULL)
		msg_perror(ERR_OUTFILE);
	if (pipe(pipex.pipe) < 0)
		msg_perror(ERR_PIPE);
	pipex.path = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.path, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	parent_free(&pipex);
	return (0);
}
