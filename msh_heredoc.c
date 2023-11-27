#include "minishell.h"

/**
 * @brief  ** BEWARE OF THIS!!!
 * 			Si le pongo un wait al padre, no muestra el heredoc bien
 * 			Me da la sensación de que mete el exit del hijo tb en el pipe
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
		dup2(cmd_nd->fd[WR], STDOUT_FILENO);
		close(cmd_nd->fd[WR]);
//		printf("DEBUG: heredoc) estoy en el hijo\n");
		input = readline("> ");
		ft_ctrl_d(data);
		while (input && ft_strcmp(input, cmd_nd->rds->end_key) != 0)
		{
			if (g_listen == 1)
			{
				g_listen = 0;
				close(cmd_nd->fd[STDOUT_FILENO]);
				exit(EXIT_SUCCESS);
			}
			hd_inputs = ft_join_free(hd_inputs, input);
			hd_inputs = ft_join_free(hd_inputs, "\n");
			ft_free_null_void_return(&input);
			input = readline("> ");
		}
		ft_free_null_void_return(&input); // por si sale del while con end_key
		ft_putstr_fd(hd_inputs, STDOUT_FILENO);
		close(cmd_nd->fd[STDOUT_FILENO]);
		ft_free_null_void_return(&hd_inputs);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(cmd_nd->fd[WR]);
		dup2(cmd_nd->fd[RD], STDIN_FILENO);
		close(cmd_nd->fd[RD]);
		waitpid(cmd_nd->pid, NULL, 0); // hace que no se vea el heredoc en tiempo real, WHY???
	}
}
