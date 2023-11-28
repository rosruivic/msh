/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_simple_lexer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:39:26 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/28 20:10:28 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cmd_lstadd_back(t_msh *data, t_cmd_lst *new)
{
	t_cmd_lst	*tmp;

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

/**
 * @brief    ** CREO UN NODO DEL TIRÓN PARA HACER TESTS **
 * 
 * @param cmd 
 * @param type 
 * @return t_rd* 
 */
static t_rd	*ft_red_alobruto(int type)
{
	t_rd	*node;
	
	type = DIR;
	node = NULL;
	if (type == SIR)
	{
		node = (t_rd *)malloc(sizeof(t_rd));
		node->type = SIR;
		node->end_key = NULL;
		node->heredoc = NULL;
		node->file = ft_strdup("in_file.txt");
		node->nx = NULL;		
	}
	else if (type == DIR)
	{
		node = (t_rd *)malloc(sizeof(t_rd));
		node->type = DIR;
		node->end_key = ft_strdup("end");
		node->heredoc = NULL;
		node->file = NULL;
		node->nx = NULL;		
	}
	else if (type == SOR)
	{
		node = (t_rd *)malloc(sizeof(t_rd));
		node->type = SOR;
		node->end_key = NULL;
		node->heredoc = NULL;
		node->file = ft_strdup("out_file.txt");
		node->nx = NULL;		
	}
	else if (type == DOR)
	{
		node = (t_rd *)malloc(sizeof(t_rd));
		node->type = DOR;
		node->end_key = NULL;
		node->heredoc = NULL;
		node->file = ft_strdup("out_file.txt");
		node->nx = NULL;
	}
	return (node);
}

static t_cmd_lst	*ft_cmd_lst_new(t_msh *data, char **cmd)
{
	t_cmd_lst	*node;
	int			i;

	(void)data;
	i = -1;
	node = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	node->c_args = ft_calloc((ft_matrix_len(cmd) + 1), sizeof(char *));
	while (cmd[++i])
		node->c_args[i] = ft_strdup(cmd[i]);
	node->c_abs_path = ft_strdup(cmd[0]);
	node->c_env_path = NULL;			// se rellena en otro momento, después
	node->rds = ft_red_alobruto(DIR);	// rellenamos a mano un nodo para hacer tests
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
void	ft_simple_lexer(t_msh *data)
{
	char	**cmd_pipe; // to split by '|' the pipeline
	char	**cmd;		// to split by ' ' every cmd
	int		mtx_len;
	int		i;
	
	i = -1;
	cmd_pipe = ft_split(data->pipeline, '|');
	mtx_len = ft_matrix_len(cmd_pipe);
	if (mtx_len == 0) // cd en pipeline solo hay espacios en blanco
	{
		ft_freedom(cmd_pipe);
		data->error = ERROR_ARGMTS;
		return ;
	}
	while (++i < mtx_len)
	{
		cmd = ft_split(cmd_pipe[i], ' ');
		ft_cmd_lstadd_back(data, ft_cmd_lst_new(data, cmd));
	}
	ft_freedom(cmd_pipe);
}
