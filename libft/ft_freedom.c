/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freedom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:31:02 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/19 18:48:02 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_freedom(char **matrix)
{	
	size_t	i;

	i = 0;
	if (matrix/*  != NULL */)
	{
		while (matrix[i])
		{
			ft_bzero(matrix[i], ft_strlen(matrix[i]));
			free(matrix[i]);
			matrix[i] = NULL;
			i++;
		}
		free(matrix);
		matrix = NULL;
	}
	return (matrix);
}
