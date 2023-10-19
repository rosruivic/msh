/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:28 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/19 19:12:58 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * @brief 		****	BEWARE OF THIS !!!   ****
 * 		THIS IS NOT THE REAL MINISHELL MAIN, only is a main to check
 * 		all the environment-vars-list's functions to be integrated in
 * 		the principal project
 * 
 * @param argc 
 * @param argv 
 * @param envp 
 * @return int 
 */
int	main(int argc, char **argv, char **envp)
{
	char	**tmp;
	
	g_data.env_lst = NULL;
	ft_duplic_envp(envp);		// CREATES THE ENVIRONMENT VAR LIST
	ft_env_lst_print();
	printf("\n\n\n");
	if (argc > 1) // 1st argmt is to add or modify one elemnt
	{
		tmp = ft_2rows_split(argv[1], '=');
		if (!tmp)
			return (0);
		printf("DEBUG main1: %s\n             %s\n\n", tmp[0], tmp[1]);
		if (ft_strchr(argv[1], '='))
			ft_env_modify_or_add_node(ft_env_lst_new(tmp, 1));
		else
			ft_env_modify_or_add_node(ft_env_lst_new(tmp, 0));
		ft_freedom(tmp);
		ft_env_lst_print();
		printf("\n\n\n");
	}
	if (argc > 2) // 2st argmt is to add or modify one elemnt
	{
		tmp = ft_2rows_split(argv[2], '=');
		if (!tmp)
			return (0);
		printf("DEBUG main2: %s\n             %s\n\n", tmp[0], tmp[1]);
		if (ft_strchr(argv[2], '='))
			ft_env_modify_or_add_node(ft_env_lst_new(tmp, 1));
		else
			ft_env_modify_or_add_node(ft_env_lst_new(tmp, 0));
		ft_freedom(tmp);
		ft_export_lst_print();
		printf("\n\n\n");
	}
	if (argc > 3) // 3rd argmt is to delete one elemnt
	{
		ft_env_lstdelone(argv[3]);
		ft_env_lst_print();
		printf("\n\n\n");
	}
	if (argc > 4) // 4rd argmt is to delete THE LIST
	{
		ft_env_lstclear();
		ft_env_lst_print();
		printf("\n\n\n");
	}
	return (0);
}
