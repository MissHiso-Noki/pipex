/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:36:48 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/26 01:06:15 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	pipex;
	// char 	*msg_errr1;
	// char	*msg_errr2;

	if (argc == 5)
	{
		initialize_struct(&pipex, argv);
		error(pipe(pipex.pipe));
		pipex.pid1 = fork();
		error(pipex.pid1);
		if (pipex.pid1 == 0)
			first_child(&pipex, argv, envp);
		else if (pipex.pid1 > 0)
		{
			pipex.pid2 = fork();
			error(pipex.pid2);
			if (pipex.pid2 == 0)
				second_child(&pipex, argv, envp);
			parent(pipex);
		}
	// 	if (ft_strchr(pipex.cmd1[0], ' '))
	// 	{
	// 		msg_errr1 = ft_strjoin(pipex.cmd1[0], ": command not found\n");
	// 		if (msg_errr1)
	// 			{
	// 				write(2, msg_errr1, ft_strlen(msg_errr1));
	// 				free(msg_errr1);
	// 			}
	// 	}
	// 	if (ft_strchr(pipex.cmd2[0], ' '))
	// 	{
	// 		msg_errr2 = ft_strjoin(pipex.cmd2[0], ": command not found\n");
	// 		if (msg_errr2)
	// 			{
	// 				write(2, msg_errr2, ft_strlen(msg_errr2));
	// 				free(msg_errr2);
	// 			}
		
	// 	}
	}
	else
		msg_error(ERR_INPUT);
	return (0);
}
