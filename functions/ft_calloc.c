/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:58:46 by ccoste            #+#    #+#             */
/*   Updated: 2023/05/29 13:59:59 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*str;

	if (size != 0 && (size * nmemb) / size == !nmemb)
	{
		return (NULL);
	}
	str = malloc(nmemb * size);
	if (!nmemb || !size)
	{
		return (str);
	}
	if (!str)
	{
		return (NULL);
	}
	ft_bzero(str, nmemb * size);
	return (str);
}