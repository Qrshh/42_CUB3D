/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:23:42 by abesneux          #+#    #+#             */
/*   Updated: 2024/08/14 19:01:59 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (NULL);
}*/

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}
/*
#include <stdio.h>
int	main(void)
{
	const char *str = "Hello, World!";
	int c = 'o';

	char *result = ft_strchr(str, c);
	if (result != NULL)
	{
		printf("Le caractère '%c' a été trouvé à la position : %ld\n", c,
			result - str);
	}
	else
	{
		printf("Le caractère '%c' n'a pas été trouvé dans la chaîne.\n",
			c);
	}
	return (0);
}*/
