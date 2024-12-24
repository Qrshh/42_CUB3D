/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:12:15 by abesneux          #+#    #+#             */
/*   Updated: 2024/11/18 14:48:03 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	total_len;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (*s1)
	{
		dest[i++] = *s1++;
	}
	while (*s2)
	{
		dest[i++] = *s2++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char const *s1 = "test";
	char const *s2 = "defou";

	printf("%s", ft_strjoin(s1, s2));
	return (0);
}*/
