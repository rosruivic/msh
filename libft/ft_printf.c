/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:00:35 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/06/09 17:28:47 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_menu(va_list args, const char text, int *len)
{
	if (text == '%')
		ft_putchar_fd_len(text, 1, len);
	else if (text == 'c')
		ft_putchar_fd_len(va_arg(args, int), 1, len);
	else if (text == 's')
		ft_putstr_fd_len(va_arg(args, char *), 1, len);
	else if (text == 'i' || text == 'd')
		ft_putnbr_fd_len(va_arg(args, int), 1, len);
	else if (text == 'u')
		ft_putuint_fd_len(va_arg(args, unsigned int), 1, len);
	else if (text == 'x' || text == 'X')
		ft_putnhex_fd_len(va_arg(args, unsigned int), 1, len, text);
	else if (text == 'p')
		ft_p0x_fd_len(va_arg(args, unsigned long long), 1, len);
}

int	ft_printf(const char *text, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, text);
	while (*text)
	{
		if (*text != '%')
			ft_putchar_fd_len(*text, 1, &len);
		else
		{
			text++;
			if (!*text)
				return (len);
			ft_menu(args, *text, &len);
		}
		text++;
	}
	va_end(args);
	return (len);
}

/* 			if (*text == '%')
				ft_putchar_fd_len(*text, 1, &len);
			else if (*text == 'c')
				ft_putchar_fd_len(va_arg(args, int), 1, &len);
			else if (*text == 's')
				ft_putstr_fd_len(va_arg(args, char *), 1, &len);
			else if (*text == 'i' || *text == 'd')
				ft_putnbr_fd_len(va_arg(args, int), 1, &len);
			else if (*text == 'u')
				ft_putuint_fd_len(va_arg(args, unsigned int), 1, &len);
			else if (*text == 'x' || *text == 'X')
				ft_putnhex_fd_len(va_arg(args, unsigned int), 1, &len, text);
			else if (*text == 'p')
				ft_p0x_fd_len(va_arg(args, unsigned long long), 1, &len, text);
			else
				return (0); */