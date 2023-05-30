/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:02:28 by ccoste            #+#    #+#             */
/*   Updated: 2023/05/30 11:22:15 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strdup(const char *s)
{
	unsigned int	sizesrc;
	char			*dest;
	unsigned int	i;

	i = 0;
	sizesrc = ft_strlen(s);
	dest = malloc((sizesrc + 1) * sizeof(char));
	if (!dest)
	{
		return (NULL);
	}
	while (i < sizesrc)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
