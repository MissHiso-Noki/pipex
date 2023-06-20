/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:31:48 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/20 12:14:42 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

size_t	ft_strlen(const char *s)

{
	int	i;

	i = 0;
	if (!s)
	{
		return (0);
	}
	while (s && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

//int main () {
//   char str[50];
//   int len;

//   strcpy(str, "This is tutorialspoint.com");

//   len = strlen(str);
//   printf("Length of |%s| is |%d|\n", str, len);

//   return(0);
//}
