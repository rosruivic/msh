/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils_add_nds.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:01:43 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/29 19:28:27 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief    ***   Adds a new node to env_lst  ****
 * 
 * @param new 		New node to be added
 */
void	ft_env_lstadd_back(t_msh *data, t_env_lst *new)
{
	t_env_lst	*tmp;

	tmp = NULL;
	if (data->env_lst == NULL && new)
		data->env_lst = new;
	else if (data->env_lst && new)
	{
		tmp = data->env_lst;
		while (tmp->nx && tmp->nx->nx)
			tmp = tmp->nx;
		new->nx = tmp->nx;
		tmp->nx = new;
	}
}

void	ft_env_lstadd_front(t_msh *data, t_env_lst *new)
{
	if (data->env_lst == NULL && new)
		data->env_lst = new;
	else if (data->env_lst && new)
	{
		new->nx = data->env_lst;
		data->env_lst = new;
	}	
}
