/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:28 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/07 18:28:49 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_listen = 0;
 
/* static void	ft_leaks(void)
{
	system("leaks -q minishell");
} */

void	ft_init_msh_struct(t_msh *data)
{
	data->error = NO_ERROR;
	data->exit_code = 0;
	data->env_lst = NULL;
	data->cmd_lst = NULL;
	data->fd = 1;
	data->org_stdin = dup(STDIN_FILENO);
	data->org_stdout = dup(STDOUT_FILENO);
//	data->sig.sa_flags = SA_RESTART;
	data->sig.sa_sigaction = ft_handler;
	sigemptyset(&data->sig.sa_mask);
	data->sig.sa_flags = SA_NODEFER; // a qué inicializarlo ?
	if (sigaction(SIGINT, &data->sig, NULL) == -1)
		ft_error_signal(ERROR_SIGACTION_FAILURE);
}

/**
 * @brief  * BEWARE OF THIS!!! 
 * 	- Si no restauro el STDIN y el STDOUT, hace un exit del programa
 *  - No reiniciar data->exit_code a 0, porque si hago echo $? me mostraría siempre 0
 * @param data 
 */
void	ft_main_boucle(t_msh *data)
{
	data->pipeline = readline(">>> msh_2.0$ ");
	ft_ctrl_d(data);
	if (data->pipeline[0] != '\0')
	{
		if (g_listen == 1)
		{
			data->exit_code = 1;
			data->error = END;
		}
		else
		{
			add_history(data->pipeline);
			ft_simple_lexer(data);
			ft_simple_parser(data);
			if (data->error == NO_ERROR)
				ft_executor(data);
		}
	}
	g_listen = 0;
	ft_free_null_void_return(&data->pipeline);
	ft_cmd_lstclear(data);
	dup2(data->org_stdin, STDIN_FILENO);  	// restaura el STDIN
	dup2(data->org_stdout, STDOUT_FILENO); 	// restaura el STDOUT
	data->error = NO_ERROR;
}
/**
 * @brief 		****	MINISHELL    ****
 * 
 * @param argc 
 * @param argv 
 * @param envp 
 * @return int 
 */
int	main(int argc, char **argv, char **envp)
{
	t_msh	data;
	
//	atexit(ft_leaks);
	(void)argv;
	if (argc > 1)
		ft_error_start(argv[1], ERROR_START_NO_SUCH_FILE_OR_DIRECTORY);
	ft_init_msh_struct(&data);
	ft_duplic_envp(&data, envp);
	while (1)
		ft_main_boucle(&data);
	return (0);
}




/* EXPLICACIÓN DE DAVID PARA HEREDOCS :

int fd[2] = pipe;
char *line = NULL;
while (1)
{
	line = readline("> ");
	if (strncmp(line, here_doc, strlen(here_doc + 1)))
		break ;
	read(fd[1], line, strlen(line));
	free(line);
}
return (fd[0])
close(fd[1]); */
	