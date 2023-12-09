/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:26:43 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/09 19:32:05 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
		
/**
 * @brief 	***  ESTO ES SOLO UN PRE-ESTUDIO, ESTA PARTE LA HAREMOS JUNTAS ***
 * 
 * @param data 
 */
void	ft_executor_many_cmds(t_msh *data)
{
	t_cmd_lst	*cmd_nd;
	t_cmd_lst	*cmd_nd_prev;

	(void)data;
	(void)cmd_nd;
	(void)cmd_nd_prev;

	printf("DEBUG: ft_executor_many_cmds\n");

/* 	while (cmd_nd != NULL)
	{
		data->m_pipe_val = pipe(cmd_nd->fd);
		data->m_pid = fork();
	} */


}

/**
 * @brief   ** DETECTS IF THERE IS MORE THAN ONE COMMAND (PIPES PRESENCE) **
 *    It has 2 pointers to the cmd list:
 * 		- one to point its head
 * 		- other to walk the cmd list and preserve the previous node to get fds close
 * @param data 
 */
void	ft_executor(t_msh *data)
{
	t_cmd_lst	*cmd_nd;
//	t_cmd_lst	*cmd_nd_prev;

	cmd_nd = data->cmd_lst;
//	cmd_nd_prev = data->cmd_lst;
	if (cmd_nd->nx == NULL)	// CASE 1: one command
	{
		ft_builtin_executor(data, data->cmd_lst->c_abs_path, cmd_nd);
	}
	else					// CASE 2: more than 1 command
	{
		ft_executor_many_cmds(data);
	}
}
