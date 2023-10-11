/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:24:55 by roruiz-v          #+#    #+#             */
/*   Updated: 2022/10/25 18:29:10 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	unsigned char	search;
	size_t			i;

	src = (unsigned char *) s;
	search = (unsigned char) c;
	i = 0;
	if (n != 0)
	{
		while (*src != search && i < n - 1)
		{
			i++;
			src++;
		}
		if (*src == search)
			return (src);
		else
			return (NULL);
	}
	else
		return (NULL);
}
