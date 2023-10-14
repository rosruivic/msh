/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:16:37 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/14 18:24:10 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_lstdelone(char *del_env_nm)
{ // elimina un nodo, el que coincida con el argmto
	t_env_lst	*tmp;

	if (g_data.env_lst)
	{
		tmp = g_data.env_lst;
		while (ft_strncmp(tmp->nm, del_env_nm, ft_strlen(tmp->nm)) != 0)
		{
			tmp = tmp->next;
			if (tmp == NULL)
				return ;
		}
		ft_free_null(tmp->nm);
		ft_free_null(tmp->val);
		free(tmp);
	}		
}

void	ft_env_lstclear(void)
{ // elimina la lista completa, de principio a fin
	t_env_lst	*del_node;

	if (g_data.env_lst == NULL)
		return ;
	while (g_data.env_lst)
	{
		del_node = g_data.env_lst;
		g_data.env_lst = del_node->next;
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
		new->next = g_data.env_lst;
		g_data.env_lst = new;
	}	
}

void	ft_env_lstadd_back(t_env_lst *new)
{
	t_env_lst	*tmp;

	tmp = NULL;
	if (g_data.env_lst == NULL && new)
	{
		g_data.env_lst = new;
	}
	else if (g_data.env_lst && new)
	{
		tmp = g_data.env_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env_lst	*ft_env_lst_new(char **tmp_env)
{
	t_env_lst	*node;

	node = NULL;
	node = (t_env_lst *)malloc(sizeof(t_env_lst));
	node->nm = ft_strdup(tmp_env[0]);
	node->val = ft_strdup(tmp_env[1]);
	node->next = NULL;
	return (node);	
}
