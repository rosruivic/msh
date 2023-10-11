/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:36:01 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/08/24 13:58:11 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_join(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	s = ft_gnl_calloc(ft_gnl_strlen(s1) + ft_gnl_strlen(s2) + 1, sizeof(*s));
	if (!s)
		return (NULL);
	i = 0;
	j = -1;
	if (s1)
	{
		while (s1[i])
		{
			s[i] = s1[i];
			i++;
		}
		free(s1);
	}
	while (s2[++j])
		s[i++] = s2[j];
	return (s);
}

static char	*ft_get_line(char *remember)
{
	char	*line;
	int		len;
	int		i;

	if (!remember)
		return (NULL);
	len = 0;
	while (remember[len] != 10 && remember[len])
		len++;
	if (remember[len] == 10)
		len++;
	line = ft_gnl_calloc(len + 1, sizeof(*line));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = remember [i];
		i++;
	}
	if (i == 0)
		return (free(line), NULL);
	return (line);
}

static char	*ft_tail_remember(char *remember)
{
	char	*tail_rmb;
	int		len;
	int		pos;
	int		i;

	if (!remember)
		return (NULL);
	pos = 0;
	while (remember[pos] != 10 && remember[pos])
		pos++;
	if (remember[pos] == 10)
		pos += 1;
	len = ft_gnl_strlen(remember) - pos + 1;
	tail_rmb = ft_gnl_calloc(len + 1, sizeof(*tail_rmb));
	if (!tail_rmb)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tail_rmb[i] = remember[pos];
		i++;
		pos++;
	}
	return (free(remember), tail_rmb);
}

static char	*ft_read_file(int fd, char *remember)
{
	int		n_bytes;
	char	*reader;

	reader = ft_gnl_calloc(BUFFER_SIZE + 1, sizeof(*reader));
	if (!reader)
		return (NULL);
	n_bytes = 1;
	while (n_bytes > 0 && ft_gnl_strchr(remember, 10) == NULL)
	{
		n_bytes = read(fd, reader, BUFFER_SIZE);
		if (n_bytes == -1)
		{
			return (free(reader), free(remember), NULL);
		}
		reader[n_bytes] = '\0';
		remember = ft_join(remember, reader);
	}
	free(reader);
	return (remember);
}

char	*get_next_line(int fd)
{
	static char	*remember = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	remember = ft_read_file(fd, remember);
	line = ft_get_line(remember);
	if (!line)
	{
		free(remember);
		remember = NULL;
		return (NULL);
	}
	remember = ft_tail_remember(remember);
	return (line);
}
