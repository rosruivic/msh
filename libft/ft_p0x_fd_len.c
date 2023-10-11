/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p0x_fd_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:15:35 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/06/09 17:28:33 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_p0x_fd_len(unsigned long long p, int fd, int *len)
{
	ft_putstr_fd_len("0x", fd, len);
	ft_pp_fd_len(p, fd, len);
}
