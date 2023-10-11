/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:07:29 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/06/09 17:29:55 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd_len(char *s, int fd, int *len)
{
	int	i;

	if (!s)
	{
		write (fd, "(null)", 6);
		*len = *len + 6;
	}
	else
	{
		i = 0;
		while (s[i])
		{
			ft_putchar_fd_len(s[i], fd, len);
			i++;
		}
	}
}
