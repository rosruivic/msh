/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:16:37 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/17 20:04:39 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   Deletes the node that cointains  (->nm == del_nd)
 * 
 * @param del_nd   The ->nm string to find in the list
 */
void	ft_env_lstdelone(char *del_nd)
{
	t_env_lst	*t;    // tmp node to keep the prev node to the one to be deleted
	t_env_lst	*del;  // finded node to be deleted

	if (g_data.env_lst && del_nd)
	{
		t = g_data.env_lst;
		if (ft_strncmp(t->nm, del_nd, ft_strlen(t->nm)) != 0)
		{
			while (ft_strncmp(t->nx->nm, del_nd, ft_strlen(t->nx->nm)) != 0)
			{ // GO AHEAD'til find equiv; if gets last node, no equiv & return
				t = t->nx;
				if (t == NULL)
					return ;
			}
		}
		else // coincide el primer nodo, borrar el primer nodo
		{
			g_data.env_lst = t->nx;
			ft_free_envlst_node(t);
			return ;
		}
		// finded one equiv after 1st node: building a bridge & deleting node
		del = t->nx;
		t->nx = t->nx->nx;
		ft_free_envlst_node(del);
	}		
}

/**
 * @brief   Deletes the complete environment vars list
 * 
 */
void	ft_env_lstclear(void)
{
	t_env_lst	*del_node;

	if (g_data.env_lst == NULL)
		return ;
	while (g_data.env_lst)
	{
		printf("DEBUG: lstclear - borrando nodo\n\n");
		del_node = g_data.env_lst;
		g_data.env_lst = del_node->nx;
		ft_free_envlst_node(del_node);
	}
}

/**
 * @brief  ***  BEWARE OF THIS!!!!
 *      IF THE NEW NODE ALREADY EXISTS (->nm), then:
 * 	    	- delete & free old (->val)
 *          - && malloc & strdup new (->val)
 * 			- delete the new node (cause it's not new anymore)
 * 		ELSE:
 * 		    - lstadd_back the new node
 * 
 * @param new 
 */
void	ft_env_modify_or_add_node(t_env_lst	*new)
{
	t_env_lst	*t;
//	t_env_lst	*del;

	t = NULL;
	if (g_data.env_lst == NULL && new)
	{
		g_data.env_lst = new;
		return ;
	}
	if (g_data.env_lst && new)
	{
		t = g_data.env_lst;
		if (ft_strncmp(t->nm, new->nm, ft_strlen(t->nm)) != 0)
		{// si 1st no coincide, mira el next:
			while (ft_strncmp(t->nx->nm, new->nm, ft_strlen(new->nm)) != 0) // ****** PETA - HAZ STRCMP
			{ // GO AHEAD'til find equiv;
				if (t->nx->nx == NULL) // if gets last node, no equiv (add & return)
				{
					t->nx->nx = new;
					return ;
				}
				t = t->nx;			
			}
		}
		else // coincide el primer nodo - intercambia el nodo - FUNCIONA
		{		
			g_data.env_lst = t->nx;
			ft_free_envlst_node(t);
			ft_env_lstadd_front(new);
			return ;
		}
	}
	// coincide con cq otro nodo - ELIMINA EL STRING ANTIGUO Y STRDUPEA EL NUEVO
	ft_free_null(t->nx->val);
	t->nx->val = ft_strdup(new->val);
	ft_free_envlst_node(new);
}

t_env_lst	*ft_env_lst_new(char **tmp_env)
{
	t_env_lst	*node;

	node = (t_env_lst *)malloc(sizeof(t_env_lst));
	node->nm = ft_strdup(tmp_env[0]);
	node->val = ft_strdup(tmp_env[1]);
	node->nx = NULL;
	return (node);	
}
