/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 13:54:36 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/06/09 16:33:59 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* static char	**ft_freedom(char **matrix)
{	
	size_t	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return (NULL);
} */

static size_t	ft_calcrows(const char *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			words++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}	
	return (words);
}

/**
 * @brief Recorre el string y posiciona, cada vez, un índice (w_ini) al 
 * 				principio de cada "palabra" mientras el índice (i) avanza hasta
 * 				el carácter inmediatamente posterior al final de dicha palabra; la 
 * 				diferencia entre ambos índices establece la longitud de la palabra 
 * 				de que se trate en ese momento. Con esos datos, pasamos la info a 
 * 				ft_substr, que se encarga de reservar la memoria para cada palabra 
 * 				dentro del segundo nivel de la matriz y le pasa el contenido. 
 * @param matrix La matriz con los punteros de punteros ya creados
 * @param s El string original con la "frase" a dividir
 * @param c El carácter separador de palabras (se elimina de la frase)
 * @param words El número de palabras que contiene la "frase"
 * @return char** El puntero a la matriz
 */
static char	**ft_matrix_pos(char **matrix, const char *s, char c, size_t words)
{
	size_t	word;
	size_t	i;	
	size_t	w_ini;

	word = 0;
	i = 0;
	while (word < words && s[i] != '\0')
	{	
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			w_ini = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			matrix[word] = ft_substr(s, (unsigned int)w_ini, (i - w_ini));
			if (!matrix[word])
				return (ft_freedom(matrix));
		}
		word++;
	}
	return (matrix);
}

char	**ft_split(char const *s, char c)
{
	char		**matrix;
	size_t		words;

	words = ft_calcrows(s, c);
	matrix = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!matrix)
		return (NULL);
	matrix = ft_matrix_pos(matrix, s, c, words);
	return (matrix);
}
