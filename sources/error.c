/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:12:12 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/13 17:39:20 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	msg(char *error)
{
	write(1, error, ft_strlen(error));
	return (1);
}

void	msg_perror(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}
