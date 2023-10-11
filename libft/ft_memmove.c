/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:57:18 by roruiz-v          #+#    #+#             */
/*   Updated: 2022/10/10 17:19:27 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;
	size_t	counter;

	d = (char *) dst;
	s = (char *) src;
	if (len == 0)
		return (dst);
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst < src)
	{
		counter = 0;
		while (counter < len)
		{
			d[counter] = s[counter];
			counter++;
		}
	}
	else
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	return (dst);
}

// Other way to do the last while (but uses more than 25 lines):
// (declaring size_t 	j)
//	j = len - 1;
//		while (j > 0)
//		{
//			d[j] = s[j];
//			j--;
//		}
//		d[j] = s[j];