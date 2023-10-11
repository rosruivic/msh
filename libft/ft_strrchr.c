/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 12:54:37 by roruiz-v          #+#    #+#             */
/*   Updated: 2022/10/01 14:14:40 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	search;
	const char		*ini_point;

	search = (unsigned char) c;
	ini_point = s;
	while (*s != '\0')
		s++;
	while (s > ini_point && *s != search)
		s--;
	if (*s == search)
		return ((char *) s);
	else
		return (NULL);
}
