/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:54:26 by roruiz-v          #+#    #+#             */
/*   Updated: 2022/10/19 12:58:42 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	len;

	if (!s1 && !s2)
	{
		newstr = (char *)ft_calloc(1, sizeof(char));
		if (!newstr)
			return (NULL);
		return (newstr);
	}
	len = ft_strlen(s1) + ft_strlen(s2);
	newstr = (char *)ft_calloc((len + 1), sizeof(char));
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, ft_strlen(s1) + 1);
	ft_strlcpy(newstr + ft_strlen(newstr), s2, ft_strlen(s2) + 1);
	return (newstr);
}
