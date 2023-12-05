/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redir_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:40:41 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/05 02:58:00 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief  ** BEWARE OF THIS!!!
 * 	Creo que con el ctrl+D se cambia la global del padre, pero no la del hijo,
 *  por eso el hijo debe enterarse de otra manera de que se ha pulsado ctrl+D.
 *  Una manera de que el hijo se entere de la señal 
 * 
 *  FIXED: el dup2 debe estar DESPUÉS de la captura
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
		close(cmd_nd->fd[RD]);
		input = readline("> ");
		ft_ctrl_d(data);
		if (g_listen == 1) // 
		{
			printf("DEBUG_1: ft_redir_heredoc) G_LISTEN = 1\n");
			ft_free_null_void_return(&hd_inputs);
			exit(1);
		}
		while (input[0] != '\0' && ft_strcmp(input, cmd_nd->rds->end_key) != 0)
		{
			hd_inputs = ft_join_free(hd_inputs, input);
			hd_inputs = ft_join_free(hd_inputs, "\n");
			ft_free_null_void_return(&input);
			input = readline("> ");
			if (g_listen == 1) // 
			{ // no consigo que entre aquí
				printf("DEBUG_2: ft_redir_heredoc) G_LISTEN = 1\n");
				ft_free_null_void_return(&hd_inputs);
				exit(1);
			}
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

		/*  ESTA PARTE TAN IMPORTANTE NO FUNCIONA, EL PADRE NO AVERIGUA EL EXIT STATUS BIEN
		 *  PERO ESTOY USANDO EL VALOR DE LA GLOBAL LUEGO EN BUILTIN EXECUTOR,
		 *  Y ESO SÍ FUNCIONA, AUNQUE TENGO QUE PONER A MANO EL EXIT_CODE = 1 */
/*  		if (WIFEXITED(exit_code)) // si el hijo terminó normalmente (con un exit)
		{ */
			data->exit_code = WEXITSTATUS(exit_code); // no consigo que devuelva el 1 si fue exit_failure
			if (data->exit_code != 0)
				data->error = END;
/*		}
		else // el hijo no acabó normalmente con exit (con un kill enviado por el padre)
		{
			data->exit_code = 1;
			data->error = END;
		} */
		printf("DEBUG: ft_redir_heredoc) data->exit_code = %d\n", data->exit_code);
		printf("DEBUG: ft_redir_heredoc) data->error = %d\n", data->error);
	}
}
