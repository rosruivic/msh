/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:09:59 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/06/09 17:29:25 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd_len(int n, int fd, int *len)
{
	if (n == -2147483648)
		ft_putstr_fd_len("-2147483648", fd, len);
	else if (n < 0)
	{
		ft_putchar_fd_len('-', fd, len);
		n = -n;
		ft_putnbr_fd_len(n, fd, len);
	}
	else
	{
		if (n > 9)
			ft_putnbr_fd_len(n / 10, fd, len);
		ft_putchar_fd_len(48 + (n % 10), fd, len);
	}
}
