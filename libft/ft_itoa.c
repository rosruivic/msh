/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:54:13 by roruiz-v          #+#    #+#             */
/*   Updated: 2022/10/31 13:47:15 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_calcpositions(int n)
{
	int	positions;

	positions = 1;
	while (n >= 10)
	{
		n = n / 10;
		positions++;
	}
	return (positions);
}

static char	*ft_fillstr(int n, char *nbr, unsigned int positions, char neg)
{
	while (positions > 0)
	{
		nbr[positions - 1] = 48 + (n % 10);
		n = n / 10;
		positions--;
	}
	if (neg == '-')
		nbr[0] = neg;
	return (nbr);
}

static char	*ft_swapmin(char *nbr)
{
	int		i;

	i = 2;
	while (i < 12)
	{
		nbr[i - 1] = nbr[i];
		i++;
	}
	nbr[i - 2] = '8';
	return (nbr);
}

static char	*ft_minvalue(void)
{
	int						n;
	unsigned int			positions;
	char					neg;
	char					*nbr;

	n = 214748364;
	positions = 11;
	neg = '-';
	nbr = (char *)ft_calloc((size_t)12, sizeof(char));
	if (!nbr)
		return (NULL);
	nbr = ft_fillstr(n, nbr, positions, neg);
	nbr = ft_swapmin(nbr);
	return (nbr);
}

char	*ft_itoa(int n)
{
	char			*nbr;
	unsigned int	positions;
	char			neg;

	positions = 0;
	neg = '+';
	if (n < 0 && n != -2147483648)
	{
		neg = '-';
		positions = 1;
		n = n * (-1);
	}
	else if (n == -2147483648)
		return (ft_minvalue());
	positions = positions + ft_calcpositions(n);
	nbr = (char *)ft_calloc((size_t)positions + 1, sizeof(char));
	if (!nbr)
		return (NULL);
	nbr = ft_fillstr(n, nbr, positions, neg);
	return (nbr);
}
