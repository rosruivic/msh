#include "minishell.h"

/**
 * @brief  ** BEWARE OF THIS!!!
 * 			Si le pongo un wait al padre, no muestra el heredoc bien
 * 			Me da la sensación de que mete el exit del hijo tb en el pipe
 *  FIXED: el problema era que el dup2 debe estar DESPUÉS de la captura
 * @param data 
 * @param cmd 
 */
void	ft_heredoc(t_msh *data, t_cmd_lst *cmd_nd)
{
	char	*hd_inputs;
	char	*input;

	hd_inputs = NULL;
	input = NULL;
	cmd_nd->pipe_val = pipe(cmd_nd->fd);
	if (cmd_nd->pipe_val < 0)
	{
		ft_error_pipes_forks(data, ERROR_PIPE_CREATION);
		exit(EXIT_FAILURE);
	}
//	printf("DEBUG: heredoc) estoy antes del fork\n");
	cmd_nd->pid = fork();
	if (cmd_nd->pid < 0)
	{
		ft_error_pipes_forks(data, ERROR_PID);
		exit(EXIT_FAILURE);
	}
	else if (cmd_nd->pid == 0)
	{
		close(cmd_nd->fd[RD]);
		input = readline("> ");
		ft_ctrl_d(data);
		while (input && ft_strcmp(input, cmd_nd->rds->end_key) != 0)
		{
			if (g_listen == 1)
			{
				g_listen = 0;
				close(cmd_nd->fd[STDOUT_FILENO]);
//				dup2(data->org_stdin, STDIN_FILENO); // restaurando (en el hijo)
//				close(data->org_stdin);
				dup2(data->org_stdout, STDOUT_FILENO);
				close(data->org_stdout);
				exit(EXIT_FAILURE);
			}
			hd_inputs = ft_join_free(hd_inputs, input);
			hd_inputs = ft_join_free(hd_inputs, "\n");
			ft_free_null_void_return(&input);
			input = readline("> ");
		}
		ft_free_null_void_return(&input);
		dup2(cmd_nd->fd[WR], STDOUT_FILENO);
		close(cmd_nd->fd[WR]);
		ft_putstr_fd(hd_inputs, STDOUT_FILENO);
		close(cmd_nd->fd[STDOUT_FILENO]);
//		dup2(data->org_stdin, STDIN_FILENO); // restaurando
//		close(data->org_stdin);
		ft_free_null_void_return(&hd_inputs);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(cmd_nd->fd[WR]);
		dup2(cmd_nd->fd[RD], STDIN_FILENO);
		close(cmd_nd->fd[RD]);
		waitpid(cmd_nd->pid, &data->exit_code, 0);
/* 		if (data->exit_code == EXIT_FAILURE)
		{
			dup2(data->org_stdin, STDIN_FILENO); // AQUÍ NOOOOO
			close(data->org_stdin);
			dup2(data->org_stdout, STDOUT_FILENO);
			close(data->org_stdout);
		} */
	}
}
