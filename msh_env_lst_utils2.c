/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:59:38 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/16 13:01:03 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_lst_print(void)
{
	t_env_lst *ptr;

	ptr = g_data.env_lst;
	while (ptr != NULL)
	{
		printf("%s=%s\n", ptr->nm, ptr->val);
		ptr = ptr->next;
	}
}

void	ft_duplic_envp(char **envp)
{
	int			i;
	char		**tmp_env;
	
	i = -1;
	while (envp[++i])
	{
		tmp_env = ft_split(envp[i], '=');
		ft_env_lstadd_back(ft_env_lst_new(tmp_env));	
		ft_freedom(tmp_env);		
	}
}
