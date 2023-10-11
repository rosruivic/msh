/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pp_fd_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:14:03 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/06/09 17:28:40 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_pp_fd_len(unsigned long long p, int fd, int *len)
{
	char	base;

	base = "0123456789abcdef" [p % 16];
	if (p > 15)
		ft_pp_fd_len(p / 16, fd, len);
	ft_putchar_fd_len(base, fd, len);
}
