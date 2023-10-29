/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_simple_lexer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:39:26 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/29 19:48:42 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cmd_lstadd_back(t_msh *data, t_cmd_lst *new)
{
	t_env_lst	*tmp;

	tmp = NULL;
	if (data->cmd_lst == NULL && new)
		data->cmd_lst = new;
	else if (data->cmd_lst && new)
	{
		tmp = data->cmd_lst;
		while (tmp->nx && tmp->nx->nx)
			tmp = tmp->nx;
		new->nx = tmp->nx;
		tmp->nx = new;
	}
}

static t_cmd_lst	*ft_cmd_lst_new(char **cmd)
{
	t_cmd_lst	*node;

	node = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	node->env_path = ft_strdup(cmd[0]);
	node->cmd_args = ft_strdup(cmd[1]);
	node->nx = NULL;
	ft_freedom(cmd);
	return (node);
}

/**
 * @brief 		*****     BEWARE OF THIS !!!!!!   *****
 * 	   This is a false lexer, it's only a practical way to test things
 * 
 * @param data 
 * @param pipeline 
 */
void	ft_lexer(t_msh *data, char *pipeline)
{
	char **cmd;
	
	cmd = ft_split(pipeline, " ");
	ft_cmd_lstadd_back(data, ft_cmd_lst_new(cmd));
	ft_free_null(pipeline);
}
