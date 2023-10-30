/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils_add_nds.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:01:43 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/30 14:07:02 by roruiz-v         ###   ########.fr       */
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

/**
 * @brief     *****    BEWARE OF THIS !!!!!!    *****
 * 
 * 		THIS IS A TRYING TO USE THE SAME FT TO ADD NODES TO
 * 		DIFFERENT TYPES OF LISTS, ACTUALLY IS IN TEST MODE
 * 
 */
void	ft_env_lstadd_front(t_msh *data, /* t_env_lst */void *new)
{
	t_env_lst	*env_nd;
	t_cmd_lst	*cmd_nd;
	
	if (sizeof(new) == sizeof(t_env_lst))
	{
		(void)cmd_nd;
		env_nd = (t_env_lst *)new;
		if (data->env_lst == NULL && env_nd)
			data->env_lst = env_nd;
		else if (data->env_lst && env_nd)
		{
			env_nd->nx = data->env_lst;
			data->env_lst = env_nd;
		}		
	}
	else if (sizeof(new) == sizeof(t_cmd_lst))
	{
		(void)env_nd;
		cmd_nd = (t_cmd_lst *)new;
		if (data->cmd_lst == NULL && cmd_nd)
			data->cmd_lst = cmd_nd;
		else if (data->cmd_lst && cmd_nd)
		{
			cmd_nd->nx = data->cmd_lst;
			data->cmd_lst = cmd_nd;
		}
	}	
}
