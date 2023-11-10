/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:30:00 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/10 00:47:03 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_status(t_msh *data, int error)
{
	if (error == END)
		data->error = END;
	else if (error == ERROR_NO_PATHS)
	{
		ft_putstr_fd("Error, no existe la variable PATH\n", 2);
		error = NO_ERROR;
	}
	else if (error == ERROR_CMD_NOT_EXISTS)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(data->cmd_lst->c_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		error = NO_ERROR;
	}
	else if (error == ERROR_CHDIR_FAILURE)
	{
		ft_putstr_fd("msh: cd: ", 2);
		ft_putstr_fd(data->cmd_lst->c_args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		error = NO_ERROR;
	}
	else if (error == ERROR_CHDIR_OLDPWD_NOT_SET)
	{
		ft_putstr_fd("msh: cd: OLDPWD not set\n", 2);
		error = NO_ERROR;
	}
	else if (error == ERROR_NO_SUCH_FILE_OR_DIRECTORY)
	{ // cuando al env le pongo argumentos, por ejemplo, pero no hay que implementarlo
		ft_putstr_fd(data->cmd_lst->c_args[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(data->cmd_lst->c_args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		error = NO_ERROR;
	}
	else if (error == ERROR_PID)
		ft_putstr_fd("Error PID\n", 2);
}
