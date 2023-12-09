/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_simple_lexer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:39:26 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/09 20:11:38 by roruiz-v         ###   ########.fr       */
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

static t_rd	*ft_redir_lst_new_heredoc(char *end_key)
{
	t_rd	*rd_nd;
	
	rd_nd = (t_rd *)malloc(sizeof(t_rd));
	rd_nd->type = DIR;
	rd_nd->end_key = ft_strdup(end_key);
	rd_nd->heredoc = NULL;
	rd_nd->file = NULL;
	rd_nd->nx = NULL;
	return (rd_nd);
}

static t_rd	*ft_redir_lst_new_file(char *file, int type)
{
	t_rd	*rd_nd;
	
	rd_nd = (t_rd *)malloc(sizeof(t_rd));
	rd_nd->type = type;
	rd_nd->end_key = NULL;
	rd_nd->heredoc = NULL;
	rd_nd->file = ft_strdup(file);
	rd_nd->nx = NULL;
	return (rd_nd);
}

static void	ft_redir_lstadd_back(t_cmd_lst *cmd_nd, t_rd *new)
{
	t_rd	*tmp;

	tmp = NULL;
	if (cmd_nd->rds == NULL && new)
		cmd_nd->rds = new;
	else if (cmd_nd->rds && new)
	{
		tmp = cmd_nd->rds;
		while (tmp->nx && tmp->nx->nx)
			tmp = tmp->nx;
		new->nx = tmp->nx;
		tmp->nx = new;
	}
}

/**
 * @brief    ** CREO NODOS DEL TIRÓN PARA HACER TESTS **
 * 
 * @param cmd 
 * @param type 
 * @return t_rd* 
 */
static void ft_redir_alobruto(t_cmd_lst *cmd_nd, int type)
{
	t_rd	*rd_nd;
	int		n_redirs = 0;
	int		i = -1;
	
	rd_nd = NULL;
	if (type == DIR)
	{
		while (++i < n_redirs)
			ft_redir_lstadd_back(cmd_nd, ft_redir_lst_new_heredoc(ft_itoa(i)));
	}
	else if (type == SIR)
	{
		while (++i < n_redirs)
			ft_redir_lstadd_back(cmd_nd, ft_redir_lst_new_file("infile", SIR));	
	}
	else if (type == SOR)
	{
		while (++i < n_redirs)
			ft_redir_lstadd_back(cmd_nd, ft_redir_lst_new_file("outfile", SOR));
	}
	else// if (type == DOR)
	{
		while (++i < n_redirs)
			ft_redir_lstadd_back(cmd_nd, ft_redir_lst_new_file("outfile", DOR));
	}
}

static t_cmd_lst	*ft_cmd_lst_new(t_msh *data, char **cmd)
{
	t_cmd_lst	*cmd_nd;
	int			i;

	(void)data;
	i = -1;
	cmd_nd = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	cmd_nd->c_args = ft_calloc((ft_matrix_len(cmd) + 1), sizeof(char *));
	while (cmd[++i])
		cmd_nd->c_args[i] = ft_strdup(cmd[i]);
	cmd_nd->c_abs_path = ft_strdup(cmd[0]);
	cmd_nd->c_env_path = NULL;		// se rellena en otro momento, después
	cmd_nd->rds = NULL;
	/**************************************************************************/
	ft_redir_alobruto(cmd_nd, DOR);	// rellenamos a mano 1 o varios nodos pa'hacer tests
	/**************************************************************************/
	cmd_nd->nx = NULL;
	ft_freedom(cmd);
	return (cmd_nd);
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
