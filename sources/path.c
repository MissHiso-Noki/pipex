/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:58:06 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/23 13:48:43 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**find_paths_and_split(char **envp)
{
	char	*envp_path;
	char	**paths;
	int		i;

	if (!envp)
		return (NULL);
	envp_path = NULL;
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			envp_path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			break ;
		}
	}
	paths = ft_split(envp_path, ':');
	if (envp_path)
		free(envp_path);
	return (paths);
}

char	**paths_add_slash(t_pipe *pipex, char **paths, char *cmd)
{
	int		i;
	char 	*tmp;

	paths = find_paths_and_split(paths);
	if (!paths || ft_strchr(cmd, '/') != NULL)
	{
		find_absolut_path(pipex, paths, cmd);
	}
	i = -1;
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/");
		free(tmp);
	}

	return (paths);
}

char	*cmd_exist(t_pipe *pipex, char	*cmd, char **paths)
{
	char	*cmd_path;
	int		i;

	if (!cmd)
		return (NULL);
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '/')
		{
			if (access(cmd, 0 | 1) == 0)
				return (cmd);
			return (NULL);
		}
	}
	paths = paths_add_slash(pipex, paths, cmd);
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, 0 | 1) == 0)
		{
			free_tab(paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free_tab(paths);
	return (NULL);
}
