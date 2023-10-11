/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnhex_fd_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:12:40 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/06/09 17:29:45 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnhex_fd_len(unsigned int n, int fd, int *len, const char text)
{
	char	base;

	if (text == 'x')
		base = "0123456789abcdef" [n % 16];
	else
		base = "0123456789ABCDEF" [n % 16];
	if (n > 15)
		ft_putnhex_fd_len(n / 16, fd, len, text);
	ft_putchar_fd_len(base, fd, len);
}

// ESTO FUNCIONA TAMBIÉN:
/*
{
 	if (n > 15)
		ft_putnhex_fd_len(n / 16, fd, len, text);
	if ((n % 16) < 10) // imprimir del 0 al 9
		ft_putchar_fd_len(48 + (n % 16), fd, len);
	else if ((*text == 'x'))
		ft_putchar_fd_len(87 + (n % 16), fd, len);
	else if ((*text == 'X'))
		ft_putchar_fd_len(55 + (n % 16), fd, len);
}
*/
