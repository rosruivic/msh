/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 13:51:02 by roruiz-v          #+#    #+#             */
/*   Updated: 2022/09/26 13:15:01 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//# include <stdlib.h>
#include "libft.h"

size_t	ft_strlen(char const *str)
{
	int	counter;

	counter = 0;
	while (str[counter] != '\0')
	{
		counter++;
	}
	return (counter);
}
