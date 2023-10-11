/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:16:37 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/11 20:24:37 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_lstdelone()
{
	
}

void	ft_env_lstclear(void)
{
	t_env_lst	*ptr;

	if (g_data.env_lst == NULL)
		return ;
	while (g_data.env_lst)
	{
		ptr = g_data.env_lst;
		g_data.env_lst = g_data.env_lst->next;
		ft_env_lstdelone();
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
