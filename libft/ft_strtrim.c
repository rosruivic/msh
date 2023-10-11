/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:59:26 by roruiz-v          #+#    #+#             */
/*   Updated: 2022/10/20 12:13:29 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_getstart(char const *s1, char const *set)
{
	size_t	i;
	char	stop;

	i = 0;
	stop = '0';
	while (i < ft_strlen(s1) && stop == '0')
	{
		if (ft_strchr(set, s1[i]))
			i++;
		else
			stop = '1';
	}
	return (i);
}

char	*ft_strvoid(void)
{
	char	*strvoid;

	strvoid = (char *)ft_calloc(1, sizeof(char));
	if (!strvoid)
		return (NULL);
	return (strvoid);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*newstr;
	char	stop;

	if (s1 == NULL || s1[0] == '\0')
		return (ft_strvoid());
	if (!set)
		return (ft_substr(s1, 0, ft_strlen(s1) + 1));
	j = ft_strlen(s1) - 1;
	i = ft_getstart(s1, set);
	stop = '0';
	while (j > i && stop == '0')
	{
		if (ft_strrchr(set, s1[j]))
			j--;
		else
			stop = '1';
	}
	newstr = ft_substr(s1, i, (j - i) + 1);
	return (newstr);
}
