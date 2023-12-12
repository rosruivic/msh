/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:26:43 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/12 19:32:05 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_change_fd_child(t_cmd_lst *cmd_nd, t_cmd_lst *cmd_nd_prev)
{
	close(cmd_nd->fd[RD]);					// RD pipe a su dcha no la usa, se cierra
	dup2(cmd_nd->fd[WR], STDOUT_FILENO);	// reasigno WR del pipe a su derecha
	close(cmd_nd->fd[WR]);
	if (cmd_nd_prev != NULL) // si es un comando intermedio, no el primero (ni el último)
	{
		dup2(cmd_nd_prev->fd[RD], STDIN_FILENO); // reasigno entrada: es pipe a su izquierda
		close(cmd_nd_prev->fd[RD]);
	}
}

static void	ft_exec_change_fd_parent(t_cmd_lst *cmd_nd, t_cmd_lst *cmd_nd_prev)
{
	close(cmd_nd->fd[WR]);				// WR pipe a su derecha no lo usa, se cierra
	dup2(cmd_nd->fd[RD], STDIN_FILENO); // reasigno RD del pipe a su dcha (se cierra en la sgte vuelta)
	close(cmd_nd->fd[RD]);
	if (cmd_nd_prev != NULL)			// si hay un pipe a su izquierda...
		close(cmd_nd_prev->fd[RD]);		// RD del pipe a su izq. se cierra
}

static void	ft_child_and_parent_routine(t_msh *data, t_cmd_lst *cmd_nd, t_cmd_lst *cmd_nd_prev)
{
	int	exit_code;

	if (data->m_pid == 0)
	{
		ft_exec_change_fd_child(cmd_nd, cmd_nd_prev);
		ft_builtin_executor(data, cmd_nd->c_abs_path, cmd_nd);
		exit(data->exit_code);
	}
	else
	{
		ft_exec_change_fd_parent(cmd_nd, cmd_nd_prev);
		waitpid(data->m_pid, &exit_code, 0);
		data->exit_code = WEXITSTATUS(exit_code);
	}	
}

/**
 * @brief 	***  IF THERE'S MANY CMDs:    ***
 * 		- Parent creates the pipes & wait
 * 		- Children execute each cmd (unless the last one)
 * 		- Parent execute the last cmd
 * @param data 
 */
void	ft_executor_many_cmds(t_msh *data, t_cmd_lst *cmd_nd, t_cmd_lst *cmd_nd_prev)
{
//	int	exit_code;

	while (cmd_nd->nx != NULL) // children exec all of cmds but the last one (parent do)
	{
		data->m_pipe_val = pipe(cmd_nd->fd);
		if (data->m_pipe_val < 0)
		{
			ft_error_pipes_forks(data, ERROR_PIPE_CREATION);
			break ;
		}
		data->m_pid = fork();
		if (data->m_pid < 0)
		{
			ft_error_pipes_forks(data, ERROR_PID);
			break ;
		}
		ft_child_and_parent_routine(data, cmd_nd, cmd_nd_prev);
		cmd_nd_prev = cmd_nd;
		cmd_nd = cmd_nd->nx;
	}
	if (cmd_nd_prev != NULL)					// RD del pipe a su izq. se cierra
	{ // executing last cmd:
		close(cmd_nd_prev->fd[RD]);
		ft_builtin_executor(data, cmd_nd->c_abs_path, cmd_nd);
	}
}

/**
 * @brief   ** DETECTS IF THERE'S ONLY 1 CMD OR MORE (PIPES PRESENCE) **
 *   It declares 2 pointers to the cmd list:
 * 		- one to point its head
 * 		- other to walk the cmd list and preserve the previous node to get fds close
 *   The 'if' treats the 2 cases: only 1 cmd or many cmds
 * @param data 
 */
void	ft_executor(t_msh *data)
{
	t_cmd_lst	*cmd_nd;
	t_cmd_lst	*cmd_nd_prev;

	cmd_nd = data->cmd_lst;
	cmd_nd_prev = NULL;
	if (cmd_nd->nx == NULL)
		ft_builtin_executor(data, data->cmd_lst->c_abs_path, cmd_nd);
	else
		ft_executor_many_cmds(data, cmd_nd, cmd_nd_prev);
}
