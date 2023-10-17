/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:28 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/17 18:01:46 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	main(int argc, char **argv, char **envp)
{
	char	**tmp;
	
	g_data.env_lst = NULL;
	ft_duplic_envp(envp);
	ft_env_lst_print();
	printf("\n\n\n");
	if (argc > 1) // 1st argmt is to add or modify one elemnt
	{
	//	ft_env_lstclear();
		tmp = ft_split(argv[1], '=');
		printf("DEBUG main1: %s\n       %s\n\n", tmp[0], tmp[1]);
//		ft_env_lstadd_back(ft_env_lst_new(tmp)); // FUNCIONA
		ft_env_modify_or_add_node(ft_env_lst_new(tmp));
		ft_freedom(tmp);
		ft_env_lst_print();
		printf("\n\n\n");
	}
	if (argc > 2) // 2st argmt is to add or modify one elemnt
	{
		tmp = ft_split(argv[2], '=');
		printf("DEBUG main2: %s\n       %s\n\n", tmp[0], tmp[1]);
		ft_env_modify_or_add_node(ft_env_lst_new(tmp));
		ft_freedom(tmp);
		ft_env_lst_print();
		printf("\n\n\n");
	}
	if (argc > 3) // 3rd argmt is to delete one elemnt
	{
		ft_env_lstdelone(argv[3]);
		ft_env_lst_print();
	//	ft_env_lstclear();
	//	ft_env_lst_print();
		printf("\n\n\n");
	}
	return (0);
}
