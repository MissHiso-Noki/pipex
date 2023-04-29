/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:23:29 by ccoste            #+#    #+#             */
/*   Updated: 2023/04/29 13:34:11 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/pipex.h"

void    childs_free(t_pipex *pipex)
{
    int i;

    i = 0;
    close(pipex->infile);
	close(pipex->outfile);
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
}

void    parents_free(t_pipex *pipex)
{
    int i;

    i = 0;
    close(pipex->infile);
	close(pipex->outfile);
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
}