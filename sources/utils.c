/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:16:42 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/25 19:42:27 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**get_cmd(char *s)
{
	if (!s)
		return (0);
	return (ft_split(s, ' '));
}

void	initialize_struct(t_pipe *pipex, char *argv[])
{
	pipex->cmd1 = get_cmd(argv[2]);
	pipex->cmd2 = get_cmd(argv[3]);
}

char	*find_absolut_path(t_pipe *pipex, char **paths, char *cmd)
{
	if (!paths && ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK | X_OK) == 0)
		{
			return (cmd);
		}
	}
	if (paths && access(cmd, F_OK | X_OK) == 0)
	{
		free_tab(paths);
		return (cmd);
	}
	else
		child_error(pipex, cmd, paths);
	return (NULL);
}
