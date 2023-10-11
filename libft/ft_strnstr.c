/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:24:23 by roruiz-v          #+#    #+#             */
/*   Updated: 2022/10/04 18:47:52 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
	Locates the first occurrence of the null-terminated string needle
	in the len 1st characters of string haystack.
		- Characters that appear after a `\0' character are not searched.
	RETURN VALUES:
		- If needle is an empty string, haystack is returned;
		- if needle occurs nowhere in haystack, NULL is returned;
		- otherwise, returns a pointer to the first character 
				of the first occurrence of needle.
*/

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (*needle == '\0')
		return ((char *) haystack);
	while (haystack[i] != '\0' && i + ft_strlen(needle) <= len)
	{
		if (ft_strncmp(haystack + i, needle, ft_strlen(needle)) == 0)
			return ((char *) haystack + i);
		else
			i++;
	}
	return (NULL);
}
