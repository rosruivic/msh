/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils_dupl_env.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:16:37 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/24 20:03:13 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief    DUPLICS the environment vars to a linked list
 * 		   (BEWARE OF THIS: the '=' caracter is CONTROLED, not stored)
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
		if (ft_strchr(envp[i], '='))
			ft_env_lstadd_back(ft_env_lst_new(tmp_env, 1));
		else	
			ft_env_lstadd_back(ft_env_lst_new(tmp_env, 0));
		ft_freedom(tmp_env);		
	}
}

/**
 * @brief       **** BUILTS A NODE WITH THE PARAMTRS INFO ****
 * 
 * @param tmp_env 
 * @param equal 
 * @return t_env_lst* 
 */
t_env_lst	*ft_env_lst_new(char **tmp_env, int equal)
{
	t_env_lst	*node;

	node = (t_env_lst *)malloc(sizeof(t_env_lst));
	node->nm = ft_strdup(tmp_env[0]);
	node->val = ft_strdup(tmp_env[1]);
	node->equal = equal;
	node->nx = NULL;
	return (node);	
}
