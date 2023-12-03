/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redir_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:40:41 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/03 21:23:46 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief  ** BEWARE OF THIS!!!
 * 			Si le pongo un wait al padre, no muestra el heredoc bien
 * 			Me da la sensación de que mete el exit del hijo tb en el pipe
 *  FIXED: el problema era que el dup2 debe estar DESPUÉS de la captura
 * @param data 
 * @param cmd 
 */
void	ft_redir_heredoc(t_msh *data, t_cmd_lst *cmd_nd)
{
	char	*hd_inputs;
	char	*input;
	int		exit_code;

	exit_code = 0;
	hd_inputs = NULL;
	input = NULL;
	cmd_nd->pipe_val = pipe(cmd_nd->fd);
	if (cmd_nd->pipe_val < 0)
	{
		ft_error_pipes_forks(data, ERROR_PIPE_CREATION);
		exit(EXIT_FAILURE);
	}
	cmd_nd->pid = fork();
	if (cmd_nd->pid < 0)
	{
		ft_error_pipes_forks(data, ERROR_PID);
		exit(EXIT_FAILURE);
	}
	else if (cmd_nd->pid == 0)
	{
//		data->sig.sa_sigaction = ft_handler_child;
		sigemptyset(&data->sig.sa_mask);
		data->sig.sa_flags = SA_NODEFER;
		close(cmd_nd->fd[RD]);
		input = readline("> ");
		ft_ctrl_d(data);
		while (input[0] != '\0' || ft_strcmp(input, cmd_nd->rds->end_key) != 0)
		{
			if (g_listen == 1) // 
			{ // no sé si hace algo de esto
				printf("DEBUG: ft_redir_heredoc) G_LISTEN = 1\n");
				ft_free_null_void_return(&hd_inputs);
//				exit(EXIT_FAILURE);
			}
			hd_inputs = ft_join_free(hd_inputs, input);
			hd_inputs = ft_join_free(hd_inputs, "\n");
			ft_free_null_void_return(&input);
			input = readline("> ");
			ft_ctrl_d(data);
		}
		ft_free_null_void_return(&input);
		dup2(cmd_nd->fd[WR], STDOUT_FILENO);
		close(cmd_nd->fd[WR]);
		ft_putstr_fd(hd_inputs, STDOUT_FILENO);
		ft_free_null_void_return(&hd_inputs);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(cmd_nd->fd[WR]);
		dup2(cmd_nd->fd[RD], STDIN_FILENO);
		close(cmd_nd->fd[RD]);
		waitpid(cmd_nd->pid, &exit_code, 0);
		if (WIFEXITED(exit_code))
			data->exit_code = WEXITSTATUS(exit_code);
		printf("DEBUG: ft_redir_heredoc) data->exit_code = %d\n", data->exit_code);
	}
}
