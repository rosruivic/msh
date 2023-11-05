/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:28 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/05 13:45:52 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_leaks(void)
{
	system("leaks -q minishell");
}

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
//	char	**tmp;
	t_msh	data;
	char	*pipeline;
	
	atexit(ft_leaks);
	(void)argv;
	if (argc != 1)
		return (0); // con ft_error será un error concreto
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
				ft_builtin_exec(&data, data.cmd_lst->path_cmd);
		}
		ft_free_null(pipeline);
//		ft_free_cmd_lst(&data); // HAY QUE IMPLEMENTARLA (= free_env_lst)
	}
	ft_env_lstclear(data.env_lst); // por si salimos con señales, no con exit

	return (0);
}

	/* ******************************************************************* */
	/* *  LO SIGTE, TRANSFORMAR PARA QUE SEA LLAMADO POR FTS CORRESPDTES * */
	/* ******************************************************************* */
/* 	if (argc > 1) // 1st argmt is to add or modify one elemnt (TEST)
	{
		tmp = ft_2rows_split(argv[1], '=');
		if (!tmp)
			return (0);
		printf("DEBUG main1: \n%s\n             %s\n\n", tmp[0], tmp[1]);
		if (ft_strchr(argv[1], '='))
			ft_env_modify_or_add_node(&data, ft_env_lst_new(tmp, 1));
		else
			ft_env_modify_or_add_node(&data, ft_env_lst_new(tmp, 0));
		ft_freedom(tmp);
		ft_printf("\n\n\n");
		ft_printf("\nLO QUE SIGUE ES 'env' DESPUÉS DE AÑADIR o MODIFICAR UNA VBLE DE ENTORNO NUEVA:\n\n\n");
		ft_env_lst_print(&data);
		ft_printf("\n\n\n");
	} */
/* 	if (argc > 2) // 2st argmt is to add or modify one elemnt (TEST)
	{
		tmp = ft_2rows_split(argv[2], '=');
		if (!tmp)
			return (0);
		printf("DEBUG main2: \n%s\n             %s\n\n", tmp[0], tmp[1]);
		
	// A VER CÓMO SOLUCIONAMOS EN EL FUTURO QUE EL '=' NO SE PIERDA
	// PQ EN EL FUTURO NO SERÁ EL MAIN EL QUE HAGA ESTA PARTE, SINO EL PARSER
		if (ft_strchr(argv[2], '='))
			ft_env_modify_or_add_node(&data, ft_env_lst_new(tmp, 1));
		else
			ft_env_modify_or_add_node(&data, ft_env_lst_new(tmp, 0));
		ft_freedom(tmp);
		ft_printf("\n\n\n");
		ft_printf("LO QUE SIGUE ES 'export' DESPUÉS DE AÑADIR o MODIFICAR UNA VBLE DE ENTORNO NUEVA:\n\n\n");
		ft_export_lst_print(&data);
		ft_printf("\n\n\n");
	} */
/* 	if (argc > 3) // 3rd argmt is to delete one elemnt (TEST)
	{
		ft_env_lstdelone(&data, ft_strdup(argv[3])); // QUIÉN LIBERARÁ ESTA CADENA ?
		ft_printf("\n\n\n");
		ft_printf("LO QUE SIGUE ES 'env' DESPUÉS DE ELIMINAR UNA VBLE DE ENTORNO:\n\n\n");
		ft_env_lst_print(&data);
		ft_printf("\n\n\n");
	} */
	