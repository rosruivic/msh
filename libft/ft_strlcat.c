/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:12:10 by roruiz-v          #+#    #+#             */
/*   Updated: 2022/10/04 11:04:46 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
		Concatenate strings
  		with the same input parameters and output result as snprintf.
		Take the full size of the destination buffer and guarantee NUL-termination 
			if there is room. Note that room for the NUL should be included in dstsize.
	RETURN VALUE:
		Appends string src to the end of dst.
		It will append at most dstsize - strlen(dst) - 1 characters.
		It will then NUL-terminate, 
			unless dstsize is 0 or the original dst string was longer than dstsize
			(in practice this should not happen as it means that either dstsize
			is incorrect or that dst is not a proper string).
    If the src and dst strings overlap, the behavior is undefined.
*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d;
	size_t	s;
	size_t	i;
	size_t	j;

	d = ft_strlen(dst);
	s = ft_strlen(src);
	i = 0;
	j = d;
	if (dstsize == 0)
		return (s);
	if (dstsize > d)
	{
		while (j < dstsize -1 && src[i] != '\0')
		{
			dst[j] = src[i];
			j++;
			i++;
		}
		dst[j] = '\0';
		return (d + s);
	}
	else
		return (s + dstsize);
}
