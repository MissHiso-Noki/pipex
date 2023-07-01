/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:36:48 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/29 11:48:30 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	pipex;

	if (argc == 5)
	{
		initialize_struct(&pipex, argv);
		error(&pipex, pipe(pipex.pipe));
		pipex.pid1 = fork();
		error(&pipex, pipex.pid1);
		if (pipex.pid1 == 0)
			first_child(&pipex, argv, envp);
		else if (pipex.pid1 > 0)
		{
			pipex.pid2 = fork();
			error(&pipex, pipex.pid2);
			if (pipex.pid2 == 0)
				second_child(&pipex, argv, envp);
			parent(&pipex);
		}
	}
	else
		msg_error(ERR_INPUT);
	return (0);
}
