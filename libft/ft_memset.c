/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:02:01 by roruiz-v          #+#    #+#             */
/*   Updated: 2022/09/26 15:29:24 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			counter;
	unsigned char	*str;

	counter = 0;
	str = (unsigned char *) b;
	if (len > 0)
	{
		while (counter < len)
		{
			str[counter] = c;
			counter++;
		}
	}
	return (b);
}
