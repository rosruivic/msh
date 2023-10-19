/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:01:43 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/19 16:33:20 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief    ***   BEWARE OF THIS !!!!   ****
 * 	     ****   NO SE AÑADE EL ÚLTIMO, SINO EL PENÚLTIMO !!!  ****
 * 
 * @param new 
 */
void	ft_env_lstadd_back(t_env_lst *new)
{ // PRIMERO: check if it already exists -> only change "val"
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

/**		*** 	PENDIENTE DE REESCRIBIR PARA RECORTAR LÍNEAS   ***
 * @brief  ***  BEWARE OF THIS!!!!
 *      IF THE NEW NODE ALREADY EXISTS (->nm), then:
 * 	    	- delete & free old (->val)
 *          - && malloc & strdup new (->val)
 * 			- delete the new node (cause it's not new anymore)
 * 		ELSE:
 * 		    - lstadd_back the new node
 * 
 * @param new     Node to be added || modified
 */
void	ft_env_modify_or_add_node(t_env_lst	*new)
{
	t_env_lst	*t;

	t = NULL;
	if (g_data.env_lst == NULL && new)
	{
		g_data.env_lst = new;
		return ;
	}
	if (g_data.env_lst && new)
	{
		t = g_data.env_lst;
		if (!ft_strcmp(t->nm, new->nm)) // CHECK THE FIRST NODE
		{// if no equiv, check the next nodes:
			while (!ft_strcmp(t->nx->nm, new->nm))
			{ // GO AHEAD'til find equiv;
				if (t->nx->nx == NULL) // last node with no equiv (add & end)
				{
					t->nx->nx = new;
					return ;
				}
				t = t->nx;
			}
		}
		else // coincide el primer nodo - intercambia los nodos
		{
			g_data.env_lst = t->nx;
			ft_free_envlst_node(t);
			ft_env_lstadd_front(new);
			return ;
		}
	}
	// finded equiv intermediate nodo - DELETE OLD STR Y STRDUP NEW ONE
	ft_free_null(t->nx->val);
	t->nx->val = ft_strdup(new->val);
	ft_free_envlst_node(new);
}
