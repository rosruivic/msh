/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:30:00 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/05 13:43:45 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_status(t_msh *data, int error)
{
	if (error == END)
		data->error = END;
	else if (error == ERROR_CMD_NOT_EXISTS)
		ft_putstr_fd("Error, cmd not exist\n", 2);
	else if (error == ERROR_PID)
		ft_putstr_fd("Error PID\n", 2);
}
