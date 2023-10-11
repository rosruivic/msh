/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint_fd_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:11:29 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/08/24 13:56:09 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Desconfía de esta función, posiblemente no está depurada
 * 
 * @param n 
 * @param fd 
 * @param len 
 */
void	ft_putuint_fd_len(unsigned int n, int fd, int *len)
{
	if (n > 9)
		ft_putuint_fd_len(n / 10, fd, len);
	ft_putchar_fd_len(48 + (n % 10), fd, len);
}
