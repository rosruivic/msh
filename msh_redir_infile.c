/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redir_infile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:40:27 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/30 12:51:20 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief  MIRA EL ARCHIVO 'ej_red_salida.c' DE LA CARPETA 'pipes_exercises'
 *    ¿TENGO QUE HACER UN FORK AQUÍ? ¿O QUE LO GESTIONE EL EXECUTOR?
 * @param data 
 * @param cmd_nd 
 */
void	ft_redir_infile(t_msh *data, t_cmd_lst *cmd_nd)
{
	(void)data;
	cmd_nd->fd_in = open(cmd_nd->rds->file, O_RDONLY);
	if (cmd_nd->fd_in < 0)
	{
		printf("error apertura fichero entrada: fd = %d\n", cmd_nd->fd_in);
		exit(EXIT_FAILURE);
	}
//	dup2(cmd_nd->fd_in, STDIN_FILENO);
//	close(cmd_nd->fd_in);
}
