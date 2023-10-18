/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:59:38 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/18 16:46:07 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief    BEWARE OF THIS !!!!
 * 	      (BEWARE THIS: the '=' caracter is not stored
 *                      THEN, is handed printed here)
 * 
 */
void	ft_env_lst_print(void)
{
	t_env_lst *ptr;

	ptr = g_data.env_lst;
	while (ptr != NULL)
	{
		ft_printf("%s=%s\n", ptr->nm, ptr->val);
		ptr = ptr->nx;
	}
}

/**
 * @brief    DUPLICS the environment vars in a linked list
 * 			(BEWARE THIS: the '=' caracter is not stored)
 * 
 * @param envp 
 */
void	ft_duplic_envp(char **envp)
{
	int			i;
	char		**tmp_env;
	
	i = -1;
	while (envp[++i])
	{
		tmp_env = ft_2rows_split(envp[i], '=');
		if (!tmp_env)
			return ;
		ft_env_lstadd_back(ft_env_lst_new(tmp_env));	
		ft_freedom(tmp_env);		
	}
}
