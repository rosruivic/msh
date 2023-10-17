/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:01:43 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/17 13:49:42 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_envlst_node(t_env_lst *del_node)
{
	ft_free_null(del_node->nm);
	ft_free_null(del_node->val);
	del_node = NULL;
}

void	ft_env_lstadd_back(t_env_lst *new)
{ // PRIMERO: check if it already exists -> only change "val"
	t_env_lst	*tmp;

	tmp = NULL;
	if (g_data.env_lst == NULL && new)
		g_data.env_lst = new;
	else if (g_data.env_lst && new)
	{
		tmp = g_data.env_lst;
		while (tmp->nx)
			tmp = tmp->nx;
		tmp->nx = new;
	}
}

void	ft_env_lstadd_front(t_env_lst *new)
{
	t_env_lst	*tmp;

	tmp = NULL;
	if (g_data.env_lst == NULL && new)
		g_data.env_lst = new;
	else if (g_data.env_lst && new)
	{
		new->nx = g_data.env_lst;
		g_data.env_lst = new;
	}	
}
