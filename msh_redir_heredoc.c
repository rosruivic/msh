/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redir_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:40:41 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/15 20:51:11 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * @param data 
 * @param cmd_nd 
 * @param hd_inputs 
 */
static void	ft_redic_heredoc_to_pipe(t_msh *data, t_cmd_lst *cmd_nd, char *hd_inputs)
{
	int		exit_code;

	exit_code = 0;
	cmd_nd->pipe_val = pipe(cmd_nd->fd);
	if (cmd_nd->pipe_val < 0)
		ft_error_pipes_forks(data, ERROR_PIPE_CREATION);
	cmd_nd->pid = fork();
	if (cmd_nd->pid < 0)
		ft_error_pipes_forks(data, ERROR_PID);
	else if (cmd_nd->pid == 0)
	{
		close(cmd_nd->fd[RD]);
//		dup2(cmd_nd->fd_her[WR], STDOUT_FILENO);
		dup2(cmd_nd->fd[WR], STDOUT_FILENO);
//		close(cmd_nd->fd_her[WR]);
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
//		dup2(cmd_nd->fd[WR], STDOUT_FILENO);
		waitpid(cmd_nd->pid, &exit_code, 0);
		data->exit_code = WEXITSTATUS(exit_code); // no consigo que devuelva el 1 si fue exit_failure
		if (data->exit_code != 0)
			data->error = END;
	}
}

/**
 * @brief   *** BEWARE OF THIS !!! ****
 *  si había pipes de antes, para ver lo que escribimos hay que
 *  guardar el STDOUT que venía impuesto de fuera, y
 *  restaurarlo antes de llamar a ft_redir_heredoc_to_pipe
 * 
 * @param data 
 * @param cmd 
 */
void	ft_redir_heredoc(t_msh *data, t_cmd_lst *cmd_nd, t_rd *rd_nd)
{
	char	*hd_inputs;
	char	*input;
	int		extern_stdout;

	hd_inputs = NULL;
	input = NULL;
	extern_stdout = dup(STDOUT_FILENO);
	dup2(data->org_stdout, STDOUT_FILENO);
	input = readline("> ");
	if (g_listen == 1)
		return ;
	while (input != NULL && ft_strcmp(input, rd_nd->end_key) != 0)
	{
		hd_inputs = ft_join_free(hd_inputs, input);
		hd_inputs = ft_join_free(hd_inputs, "\n");
		ft_free_null_void_return(&input);
		input = readline("> ");
		if (g_listen == 1)
		{
			ft_free_null_void_return(&hd_inputs);
			return ;
		}
	}
	ft_free_null_void_return(&input);
	dup2(extern_stdout, STDOUT_FILENO);
	ft_redic_heredoc_to_pipe(data, cmd_nd, hd_inputs);
	ft_free_null_void_return(&hd_inputs);
}
