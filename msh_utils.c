/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:17:09 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/18 16:10:47 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * @param s1 
 * @param s2 
 * @return int   returns 0 if they aren't equal
 *               returns 1 if they are equal
 */
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

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
 * @brief  Builds a 2 rows matrix, dividing by the 1st coincidence of 'c'
 * 
 * @param str 		    The string to be divided
 * @param c 		    The char to be finded to do the division
 * @return char**       If there's no the character to find, returns NULL
 */
char	**ft_2rows_split(char *str, char c)
{
	int		i;
	int		len;
	char	**matrix;

	i = -1;
	len = ft_strlen(str);
	matrix = NULL;
	while (str[++i] && str[i] != c)
		;
	if (str[i] == c && i < len - 1)
	{
		matrix = ft_calloc(3, sizeof(char *));
		if (!matrix)
			return (NULL);
		matrix[0] = ft_substr(str, 0, i);
		if (!matrix[0])
			return (ft_freedom(matrix), NULL);
		matrix[1] = ft_substr(str, i + 1, len - i);
		if (!matrix[1])
			return (ft_freedom(matrix), NULL);
	}
	return (matrix);
}
