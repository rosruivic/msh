/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:16:37 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/16 16:59:04 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_lstdelone(char *del_nd)
{ // elimina un nodo, el que coincida con el argmto
	t_env_lst	*t;
	t_env_lst	*del;

	if (g_data.env_lst)
	{
		t = g_data.env_lst;
		if (ft_strncmp(t->nm, del_nd, ft_strlen(t->nm)) != 0)
		{
			while (ft_strncmp(t->nx->nm, del_nd, ft_strlen(t->nx->nm)) != 0)
			{ // GO AHEAD until find equiv; if last node, there's no equiv & return
				t = t->nx;
				if (t == NULL)
					return ;
			}
		}
		else // coincide el primer nodo, borrar el primer nodo
		{
			printf("DEBUG: lstclear - borrando primer nodo\n");
			g_data.env_lst = t->nx;
			ft_free_null(t->nm);
			ft_free_null(t->val);
			t = NULL;
			return ;
		}
		// finded one inter equivalence: building a bridge & deleting node
		del = t->nx;
		t->nx = t->nx->nx;
		ft_free_null(del->nm);
		ft_free_null(del->val);
		del = NULL;
	}		
}

void	ft_env_lstclear(void)
{ // elimina la lista completa, de principio a fin
	t_env_lst	*del_node;

	if (g_data.env_lst == NULL)
		return ;
	while (g_data.env_lst)
	{
		printf("DEBUG: lstclear - borrando nodo\n");
		del_node = g_data.env_lst;
		g_data.env_lst = del_node->nx;
		ft_free_null(del_node->nm);
		ft_free_null(del_node->val);
		free(del_node);
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

void	ft_env_lstadd_back(t_env_lst *new)
{ // PRIMERO: check if it already exists -> only change "val"
	t_env_lst	*tmp;

	tmp = NULL;
	if (g_data.env_lst == NULL && new)
	{
		g_data.env_lst = new;
	}
	else if (g_data.env_lst && new)
	{
		tmp = g_data.env_lst;
		while (tmp->nx)
		{
			tmp = tmp->nx;
		}
		tmp->nx = new;
	}
}

t_env_lst	*ft_env_lst_new(char **tmp_env)
{
	t_env_lst	*node;

	node = NULL;
	node = (t_env_lst *)malloc(sizeof(t_env_lst));
	node->nm = ft_strdup(tmp_env[0]);
	node->val = ft_strdup(tmp_env[1]);
	node->nx = NULL;
	return (node);	
}
