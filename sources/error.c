/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:12:12 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/20 13:19:17 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int		msg_error(char *error)
{
	write(1, error, ft_strlen(error));
	return (1);
}

void	msg_perror(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

void	error(int ret)
{
	if (ret == -1)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		exit(1);
	}
}
