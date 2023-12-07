/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redir_infile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:40:27 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/07 21:04:00 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   BEWARE OF THIS !!!!
 * 		NECESITA PASARLE EL NODO DE REDIRECCIONAMIENTO
 * 		(y que funcione)
 * @param data 
 * @param cmd_nd 
 */
void	ft_redir_infile(t_msh *data, t_cmd_lst *cmd_nd, t_rd *rd_nd)
{
	(void)data;

	cmd_nd->fd_in = open(rd_nd->file, O_RDONLY);
	if (cmd_nd->fd_in < 0)
	{
		data->error = ERROR_OPEN_INFILE;
		ft_error_files(data, cmd_nd, data->error);
	}
	else
	{
		dup2(cmd_nd->fd_in, STDIN_FILENO);
		close(cmd_nd->fd_in);
	}
}

void	ft_redir_outfile(t_msh *data, t_cmd_lst *cmd_nd, t_rd *rd_nd)
{
	(void)data;

	if (cmd_nd)
	cmd_nd->fd_in = open(rd_nd->file, O_RDONLY);
	if (cmd_nd->fd_in < 0)
	{
		data->error = ERROR_OPEN_INFILE;
		ft_error_files(data, cmd_nd, data->error);
	}
	else
	{
		dup2(cmd_nd->fd_in, STDIN_FILENO);
		close(cmd_nd->fd_in);
	}
}
