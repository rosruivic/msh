/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:28 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/14 20:32:12 by roruiz-v         ###   ########.fr       */
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
	if (argc > 1)
	{
		tmp = ft_split(argv[1], '=');
		printf("DEBUG: %s\n       %s\n\n", tmp[0], tmp[1]);
		ft_env_lstadd_back(ft_env_lst_new(tmp));
		ft_freedom(tmp);
		ft_env_lst_print();
		printf("\n\n\n");
	}
/* 	if (argc > 2)
	{
		ft_env_lstdelone(argv[2]);
		ft_env_lst_print();
		printf("\n\n\n");
	} */
	return (0);
}
