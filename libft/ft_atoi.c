/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:01:21 by roruiz-v          #+#    #+#             */
/*   Updated: 2022/10/06 14:48:12 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/****************************************************************************
  Converts the initial portion of the string pointed (passing spaces until
  	finds a number (or a sign belowed by a number), and then from there 
		to last until finds a no-number character, where it stops).
	Spaces are white space, tab, rc... (isspace(3)).
	It does not start de conversion until it finds a number or only one sign 
		followed by a number. It finishes when founds a '\0' and returns value.
	RETURN VALUE: the int representation of the string found.
	***************************************************************************
	VAR j: stocks 1st number position it founds;
	VAR i--: stocks last position with a number it founds.
	(We'll walk this positions in inverted order: units, decens, centens...)
*****************************************************************************/

#include "libft.h"

static int	ft_getnum(const char *str, size_t i, int sign, int n)
{
	size_t	j;
	int		weight;

	j = i;
	weight = 1;
	while (ft_isdigit(str[i]) && str[i] != '\0')
		i++;
	while (i-- > j)
	{
		n = n + (str[i] - 48) * weight;
		weight = weight * 10;
	}
	if (sign != 0)
		return (n * sign);
	else
		return (n);
}

static int	ft_idsign(const char *str, size_t i, int sign)
{
	if (str[i] == '+')
		sign = +1;
	else if (str[i] == '-')
		sign = -1;
	return (sign);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		num;
	int		sign;

	i = 0;
	num = 0;
	sign = 0;
	while (!ft_isdigit(str[i]) && str[i] != '\0')
	{
		if (ft_isdigit(str[i]) || (str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		else if ((str[i] == '+' || str[i] == '-') && sign == 0)
		{
			sign = ft_idsign(str, i, sign);
			i++;
			if (!ft_isdigit(str[i]))
				return (0);
		}
		else
			return (0);
	}
	if (ft_isdigit(str[i]))
		return (ft_getnum(str, i, sign, num));
	return (0);
}
