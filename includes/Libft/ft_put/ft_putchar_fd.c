/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 01:31:04 by marvin            #+#    #+#             */
/*   Updated: 2023/10/24 18:05:15 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
int	main(void)
{
	char c = 'A'; // Caractère que vous souhaitez écrire
	int fd = 1;   // Utilisez 1 pour la sortie standard (stdout)

	ft_putchar_fd(c, fd);

	return (0);
}*/
