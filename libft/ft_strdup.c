/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:45:16 by roruiz-v          #+#    #+#             */
/*   Updated: 2022/10/19 12:55:58 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/* This function allocates sufficient memory for a copy of the string s1,     */
/*    does the copy, and returns a pointer to it.                             */
/* The pointer may subsequently be used as an argument to the function free.  */
/* If insufficient memory is available, NULL is returned and errno is set     */
/*    to ENOMEM.                                                              */
/* ************************************************************************** */

char	*ft_strdup(const char *s1)
{
	char		*dst;
	size_t		len;

	len = ft_strlen(s1);
	dst = (char *)ft_calloc((len + 1), sizeof(char));
	if (!dst)
		return (NULL);
	ft_memmove(dst, s1, len);
	dst[len] = '\0';
	return (dst);
}
