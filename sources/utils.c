/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:16:42 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/20 13:20:37 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**get_cmd(char *s)
{
	if (!s)
		return (NULL);
	return (ft_split(s, ' '));
}

void	cmd_not_found(char *path_cmd, char	**cmd)
{
	if (!path_cmd)
	{
		write(2, "Command not found: ", 19);
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, "\n", 1);
		exit(1);
	}
}

void	initialize_struct(t_pipe *pipex, char *argv[])
{
	pipex->cmd1 = get_cmd(argv[2]);
	pipex->cmd2 = get_cmd(argv[3]);
	pipex->infile = open(argv[1], O_RDONLY);
	error(pipex->infile);
	pipex->outfile = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	error(pipex->outfile);
}
