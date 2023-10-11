/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:28 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/11 20:20:08 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_duplic_envp(char **envp)
{
	int			i;
	char		**tmp_env;
	
	i = -1;
	while (envp[++i])
	{
		tmp_env = ft_split(envp[i], '=');
		ft_env_lstadd_back(ft_msh_env_lst_new(tmp_env));	
		ft_freedom(tmp_env);		
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_data.env_lst = NULL;
	ft_duplic_envp(envp);
	ft_env_lst_print();
	return (0);
}
