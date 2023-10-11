/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:28:34 by roruiz-v          #+#    #+#             */
/*   Updated: 2022/09/26 18:24:00 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				counter;
	unsigned char		*d;
	const unsigned char	*s;

	counter = 0;
	d = (unsigned char *) dst;
	s = (const unsigned char *) src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (counter < n)
	{
		d[counter] = s[counter];
		counter++;
	}
	return (dst);
}
