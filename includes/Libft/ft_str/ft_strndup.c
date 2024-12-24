/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:20:12 by abesneux          #+#    #+#             */
/*   Updated: 2024/01/09 17:22:53 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strndup(char *str, unsigned int n)
{
	char			*dest;
	unsigned int	i;

	i = 0;
	dest = malloc(sizeof(char) * (n + 1));
	while (i < n)
	{
		dest[i] = *str;
		i++;
		str++;
	}
	dest[n] = 0;
	return (dest);
}
