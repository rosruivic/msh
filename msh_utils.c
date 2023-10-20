/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:17:09 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/20 20:52:25 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   ***** COMPARES IF TWO STRINGS ARE EXACTLY THE SAME  *****
 * 
 * @param s1 
 * @param s2 
 * @return int   returns 0 if they aren't equal
 *               returns 1 if they are equal
 */
int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = -1;
	if (!s1 || !s2)
		return (0);
	if (ft_strlen(s1) == ft_strlen(s2))
	{
		while (s1[++i])
		{
			if (s1[i] != s2[i])
				return (0);
		}
		return (1);
	}
	return (0);
}

void	ft_free_null(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}

/**
 * @brief  Builds a 2 rows matrix, dividing by 1st coincidence of 'c'
 * 			If there's no 'c', then the second row = NULL.
 * @param str 		    The string to be divided
 * @param c 		    The char to be finded to do the division
 * @return char**       
 */
char	**ft_2rows_split(char *str, char c)
{
	size_t	i;
	char	**matrix;

	i = -1;
	matrix = NULL;
	if (!str || ft_strlen(str) == 0)
		return (NULL);
	matrix = ft_calloc(3, sizeof(char *));
	if (!matrix)
		return (NULL);
	while (str[++i] && str[i] != c)
		;
	matrix[0] = ft_substr(str, 0, i);
	if (!matrix[0])
		return (ft_freedom(matrix), NULL);
	if (str[i] == c && i < ft_strlen(str) - 1) // CASO A) HAY '=' Y ALGO DETRÁS
	{
		matrix[1] = ft_substr(str, i + 1, ft_strlen(str) - i - 1); // -1 SOSPECHOSO ***
		if (!matrix[1])
			return (ft_freedom(matrix), NULL);
	}
	else if (str[i] != c || (str[i] == c && i == ft_strlen(str) - 1)) // -1 SOSPECHOSO ***
		matrix[1] = ft_calloc(1, sizeof(char));
	return (matrix);
}
