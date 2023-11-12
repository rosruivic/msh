/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:28 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/12 19:28:46 by roruiz-v         ###   ########.fr       */
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
	data->sig.sa_sigaction = ft_handler;
	sigemptyset(&data->sig.sa_mask);
	data->sig.sa_flags = SA_NODEFER;
	data->error = 0;
	data->exit_code = 0;
	data->env_lst = NULL;
	data->cmd_lst = NULL;
	data->fd = 1;
}

void	ft_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (SIGINT == sig)
	{
		g_listen = 1;
		printf("has pulsado ctrl C\n");
	}
}

void	ft_ctrl_d(char *pipeline)
{
	if (!pipeline)
	{
	//	rl_replace_line("exit\n", 0);
		ft_putstr_fd("exit\n", 1); // no puedo quitar el '^D' q se imprime
		exit(EXIT_SUCCESS);
	}
}

/* void	ft_ctrl_c(t_msh *data)
{
	
} */

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
	char	*pipeline;
	
//	atexit(ft_leaks);
	(void)argv;
	if (argc > 1)
		ft_error_start(argv[1], ERROR_START_NO_SUCH_FILE_OR_DIRECTORY);
	ft_init_msh_struct(&data);
	if (sigaction(SIGINT, &data.sig, NULL) == -1)
		ft_error_signal(ERROR_SIGACTION_FAILURE);
	ft_duplic_envp(&data, envp);
	while (data.error != END) // separar este contenido en una función
	{
		data.error = NO_ERROR;
		pipeline = readline(">>> msh-1.0$ ");
		ft_ctrl_d(pipeline);
		if (pipeline[0] != '\0')
		{
			add_history(pipeline);
			ft_simple_lexer(&data, pipeline); // crea cmd_lst (tantos nds como pipes + 1)
			ft_simple_parser(&data);
			if (data.error == NO_ERROR) // lexer o parser no detectan error
				ft_builtin_exec(&data, data.cmd_lst->c_abs_path);
		}
		ft_free_null_void_return(&pipeline);
		ft_cmd_lstclear(&data);
	}
	return (0);
}
	