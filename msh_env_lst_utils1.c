/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:16:37 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/19 17:37:13 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_envlst_node(t_env_lst *del_node)
{
	ft_free_null(del_node->nm);
	ft_free_null(del_node->val);
	del_node = NULL;
}

/**
 * @brief   Deletes the node that cointains  (->nm == del_nd)
 * 
 *          *** 	IT WILL BE CALLED BY COMMAND "unset"   ***
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
		if (!ft_strcmp(t->nm, del_nd))
		{
			while (!ft_strcmp(t->nx->nm, del_nd))
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
		ft_printf("DEBUG: lstclear - borrando nodo\n\n");
		del_node = g_data.env_lst;
		g_data.env_lst = del_node->nx;
		ft_free_envlst_node(del_node);
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
		if (ft_strchr(envp[i], '='))
			ft_env_lstadd_back(ft_env_lst_new(tmp_env, 1));
		else	
			ft_env_lstadd_back(ft_env_lst_new(tmp_env, 0));
		ft_freedom(tmp_env);		
	}
}

t_env_lst	*ft_env_lst_new(char **tmp_env, int equal)
{
	t_env_lst	*node;

	node = (t_env_lst *)malloc(sizeof(t_env_lst));
	node->nm = ft_strdup(tmp_env[0]);
	node->val = ft_strdup(tmp_env[1]);
	if (equal)
		node->equal = equal;
	else
		node->equal = 0;
	node->nx = NULL;
	return (node);	
}
