/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:09:04 by abesneux          #+#    #+#             */
/*   Updated: 2024/01/10 17:21:26 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s2[i] - s1[i]);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_strncmp("Hello", "Hellol", 9));
	printf("%d", strncmp("Hello", "Hellol", 9));

}*/
