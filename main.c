/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:28 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/10 21:30:23 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	ft_leaks(void)
{
	system("leaks -q minishell");
} */

void	ft_init_msh_struct(t_msh *data)
{
	data->error = 0;
	data->env_lst = NULL;
	data->cmd_lst = NULL;
	data->fd = 1;
}

/**
 * @brief 		****	BEWARE OF THIS !!!   ****
 * 
 * 		THIS IS NOT THE REAL MINISHELL MAIN, only is a main to check
 * 		all the environment-vars-list's functions before to be integrated
 * 		in the principal project
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
	data.env_lst = NULL;
	ft_duplic_envp(&data, envp);
	while (data.error != END)
	{
		data.error = NO_ERROR;
		pipeline = readline(">>> msh-1.0$ ");
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
	