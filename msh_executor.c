/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:26:43 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/27 23:31:54 by roruiz-v         ###   ########.fr       */
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
	(void)data;
	printf("DEBUG: ft_executor_many_cmds\n");
/*
 // el primer comando se ejecuta antes del while:
		if (pipe(cmd_nd->fd) == NULL)
			ft_error_status(data, ERROR_PIPE_CREATION);
		data->pid = fork();
		if (data->pid < 0)
			ft_error_status(data, ERROR_PID);
		else if (data->pid == 0) 	// 1st CHILD
		{ // si hay redirecc. de entrada al principio, podría ser algo así:
//			if (data->fd_infile > 0) // (sabremos que no hay redir_entrada si fd_infile = -42):
//			{
//				data->fd_infile = open("file_in", O_RDONLY); // si fue HEREDOC, se creó tb file.tmp
//				if (data->fd_infile < 0)
//					ft_error_status(data, ERROR_OPEN_FILE); (con su EXIT_FAILURE)
//				dup2(data->fd_infile, STDIN_FILENO); // asigna extremo READ
//				close(data->fd_infile); // una vez duplicado, ya no hace falta
//			}
//			else
//				close(cmd_nd->fd[0]);  // si no hay redirec. entrada, no hay entrada, cerramos
			dup2(cmd_nd->fd[1], STDOUT_FILENO); // asigna extremo WRITE
			close(cmd_nd->fd[1]); // una vez duplicado, ya no hace falta, cerramos
			ft_builtin_exec_pipes(data, cmd_nd->c_abs_path, cmd_nd);
			exit(data->exit_code);
		}
		else // FATHER of the rest of children except the first
		{
			close(cmd_nd->fd[1]);		// cierra el extremo de escritura
			wait(&data->exit_code);
			cmd_nd = cmd_nd->nx;		// aquí cmd_nd se pone por delante de cmd_nd_prev
			while (cmd_nd)				// por cada comando a partir del segundo
			{
				if (pipe(cmd_nd->fd) == NULL); 	// cada nodo-comando tiene su pareja
					ft_error_status(data, ERROR_PIPE_CREATION);
				data->pid = fork(); 	// el pip es único, está en data principal
				if (data->pid < 0)
					ft_error_status(data, ERROR_PID);
				else if (data->pid == 0 && cmd_nd->nx)	// 2nd CHILDREN tienen q dup STDIN & STDOUT
				{ // no es el último comando, no aplica el redic. de salida aún
					dup2(cmd_nd->fd[0], STDIN_FILENO); // asigna extremo READ
					close(cmd_nd->fd[0]); 	// una vez tenemos el duplicado, cerrar original
					dup2(cmd_nd->fd[1], STDOUT_FILENO); // asigna extremo WRITE
					close(cmd_nd->fd[1]); 	// una vez tenemos el duplicado, cerrar original
					ft_builtin_exec_pipes(data, cmd_nd->c_abs_path, cmd_nd);
					exit(data->exit_code);
				}
				else if (data->pid == 0 && !cmd_nd->nx)	// 2nd CHILDREN tienen q dup STDIN & STDOUT
				{ // es el último comando y puede que haya redirecc de salida:
					dup2(cmd_nd->fd[0], STDIN_FILENO); // asigna extremo READ
					close(cmd_nd->fd[0]); 	// una vez tenemos el duplicado, cerrar original
					if (data->fd_outfile == '>')
						cmd_nd->fd[1] = open("file_out", O_CREAT | O_TRUNC | O_RDWR, 0644);
					else if (data->fd_outfile == '>>')	
						cmd_nd->fd[1] = open("file_out", O_CREAT | O_APPEND | O_RDWR, 0644);
					dup2(cmd_nd->fd[1], STDOUT_FILENO); // asigna extremo WRITE
					close(cmd_nd->fd[1]); 	// una vez tenemos el duplicado, cerrar original
					ft_builtin_exec_pipes(data, cmd_nd->c_abs_path, cmd_nd);
					exit(data->exit_code);
				}
				else  // PADRE (NO HARÍA FALTA DECIR 'ELSE', PERO HACE BONITO)
				{
					close(cmd_nd_prev->fd[0]);	// extremo lectura nodo previo al actual
					close(cmd_nd->fd[1]); 		// cierra el extremo de escritura
					wait(&data->exit_code);
				}
				cmd_nd_prev = cmd_nd_prev->nx;	// EL PREVIO AHORA SEÑALA AL ACTUAL
				cmd_nd = cmd_nd->nx; 			// EL ACTUAL AHORA SEÑALA AL SIGUIENTE
			}
			// último comando lo debería ejecutar el padre con redir. de salida (?)
		}*/
}

/**
 * @brief   *** ONLY ONE COMMAND, WITH OR NOT REDIRECTIONS ***
 *  		  
 * @param data 
 */
void	ft_executor(t_msh *data)
{
	t_cmd_lst	*cmd_nd; 	// PARA LLEVAR LA CUENTA DE LOS NODOS
	t_cmd_lst	*cmd_nd_prev; // PARA NO PERDER EL NODO ANTERIOR E IR CERRANDO FDs

	cmd_nd = data->cmd_lst;
	cmd_nd_prev = data->cmd_lst;
	if (cmd_nd->nx == NULL)	// CASO 1: solo existe un nodo = un comando
	{
		ft_builtin_executor(data, data->cmd_lst->c_abs_path, cmd_nd);
	}
	else					// CASO 2: hay pipes = varios comandos
	{
		ft_executor_many_cmds(data);
	}
}
