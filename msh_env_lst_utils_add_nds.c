/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils_add_mfy_nds.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:01:43 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/24 19:56:34 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief    ***   BEWARE OF THIS !!!!   ****
 * 	     ****     ****
 * 
 * @param new 
 */
void	ft_env_lstadd_back(t_env_lst *new)
{
	t_env_lst	*tmp;

	tmp = NULL;
	if (g_data.env_lst == NULL && new)
		g_data.env_lst = new;
	else if (g_data.env_lst && new)
	{
		tmp = g_data.env_lst;
		while (tmp->nx && tmp->nx->nx)
			tmp = tmp->nx;
		new->nx = tmp->nx;
		tmp->nx = new;
	}
}

void	ft_env_lstadd_front(t_env_lst *new)
{
	if (g_data.env_lst == NULL && new)
		g_data.env_lst = new;
	else if (g_data.env_lst && new)
	{
		new->nx = g_data.env_lst;
		g_data.env_lst = new;
	}	
}
