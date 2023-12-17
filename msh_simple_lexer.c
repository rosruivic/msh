/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_simple_lexer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:39:26 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/17 18:17:42 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cmdadd_back(t_msh *data, t_cmd *new)
{
	t_cmd	*tmp;

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

static void	ft_redir_lstadd_back(t_cmd *cmd_nd, t_rd *new)
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
static void ft_redir_alobruto(t_cmd *cmd_nd, int type)
{
	t_rd	*rd_nd;
//	int		n_redirs = 0;
	int		i = -1;
	
	rd_nd = NULL;
	if (type == DIR)
	{
		while (++i < 1)  // en lugar de comparar con n_redirs, comparo con un nº fijo
			ft_redir_lstadd_back(cmd_nd, ft_redir_lst_new_heredoc(ft_itoa(i + 1)));
	}
	else if (type == SIR)
	{
		while (++i < 1) // en lugar de comparar con n_redirs, comparo con un nº fijo
			ft_redir_lstadd_back(cmd_nd, ft_redir_lst_new_file("infile", SIR));	
	}
	else if (type == SOR)
	{
		while (++i < 1) // en lugar de comparar con n_redirs, comparo con un nº fijo
			ft_redir_lstadd_back(cmd_nd, ft_redir_lst_new_file("outfile", SOR));
	}
	else if (type == DOR)
	{
		while (++i < 1) // en lugar de comparar con n_redirs, comparo con un nº fijo
			ft_redir_lstadd_back(cmd_nd, ft_redir_lst_new_file("outfile", DOR));
	}
	else if (type == CODED)// hago las combinaciones que me interesan:
	{
//		ft_redir_lstadd_back(cmd_nd, ft_redir_lst_new_file("infile", SIR));
		ft_redir_lstadd_back(cmd_nd, ft_redir_lst_new_heredoc(ft_itoa(i + 2)));
		ft_redir_lstadd_back(cmd_nd, ft_redir_lst_new_heredoc(ft_itoa(i + 3)));
		ft_redir_lstadd_back(cmd_nd, ft_redir_lst_new_heredoc(ft_itoa(i + 4)));
		ft_redir_lstadd_back(cmd_nd, ft_redir_lst_new_heredoc(ft_itoa(i + 5)));
		ft_redir_lstadd_back(cmd_nd, ft_redir_lst_new_heredoc(ft_itoa(i + 6)));
//		ft_redir_lstadd_back(cmd_nd, ft_redir_lst_new_file("infile_2", SIR));
	}
	else // in case of NONE
		return ;
}

/**
 * @brief   ** CREACIÓN E INICIALIZACIÓN DE NODOS DE COMANDOS **
 * 
 *  CREA NEW NODE (init), CREA SU RD_LST (init), y LO RETORNA; 
 * 		 (OUTSIDE, IS ADDED TO CMD_LST)
 *  Al crear los nodos de comandos, se inicializan los fd a los originales.
 *  El ulterior flujo de redirecciones se encarga de modificarlos cuando
 *     corresponda.
 * @param data 
 * @param cmd 
 * @param type 		e_type
 * @return t_cmd* 
 */
static t_cmd	*ft_cmd_new(t_msh *data, char **cmd, int type)
{
	t_cmd	*cmd_new;
	int			i;

	(void)data;
	i = -1;
	cmd_new = (t_cmd *)malloc(sizeof(t_cmd));
	cmd_new->c_args = ft_calloc((ft_matrix_len(cmd) + 1), sizeof(char *));
	while (cmd[++i])
		cmd_new->c_args[i] = ft_strdup(cmd[i]);
	cmd_new->c_abs_path = ft_strdup(cmd[0]);
	cmd_new->c_env_path = NULL;		// se rellena en otro momento, después

	/*********************************************************************/
	/**  CRUCIALES: sgtes cmds no reciben bien el stdin sin esto:       **/
//	cmd_new->fd[RD] = dup(STDIN_FILENO);  // PROBANDO INICIALIZARLOS A MANO
//	cmd_new->fd[RD] = data->org_stdin;  // esto tb funciona y no gasta fds
//	cmd_new->fd[WR] = dup(STDOUT_FILENO); // PROBANDO INICIALIZARLOS A MANO
//	cmd_new->fd[WR] = data->org_stdout; // esto tb funciona y no gasta fds
	/*********************************************************************/
	cmd_new->rds = NULL;
	
	/*********************************************************************/
	/**  RELLENAMOS A MANO NODOS DE REDIR PA CHEQUEAR BEHAVIOUR: **/
	ft_redir_alobruto(cmd_new, type);
	/*********************************************************************/
	
	cmd_new->nx = NULL;
	ft_freedom(cmd);
	return (cmd_new);
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
	char	**cmd_name;	// to split by ' ' every cmd
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
	
	/*****************************************************************/
	/** tipificamos a mano los redireccionamientos de los comandos:  */
	/*****************************************************************/
	if (mtx_len > 0) // presencia de un solo comando
	{
		cmd_name = ft_split(cmd_pipe[0], ' ');
		ft_cmdadd_back(data, ft_cmd_new(data, cmd_name, CODED));
	}
	if (mtx_len > 1) // presencia de dos comandos (un pipe	)
	{
		cmd_name = ft_split(cmd_pipe[1], ' ');
		ft_cmdadd_back(data, ft_cmd_new(data, cmd_name, 0));
	}
	if (mtx_len > 2) // presencia de tres comandos (dos pipes)
	{
		cmd_name = ft_split(cmd_pipe[2], ' ');
		ft_cmdadd_back(data, ft_cmd_new(data, cmd_name, 0));
	}
	if (mtx_len > 3) // presencia de cuatro comandos (tres pipes)
	{
		cmd_name = ft_split(cmd_pipe[3], ' ');
		ft_cmdadd_back(data, ft_cmd_new(data, cmd_name, 0));
	}
	if (mtx_len > 4) // presencia de cinco comandos (cuatro pipes)
	{
		cmd_name = ft_split(cmd_pipe[4], ' ');
		ft_cmdadd_back(data, ft_cmd_new(data, cmd_name, 0));
	}
	if (mtx_len > 5) // presencia de seis comandos (cinco pipes)
	{
		cmd_name = ft_split(cmd_pipe[5], ' ');
		ft_cmdadd_back(data, ft_cmd_new(data, cmd_name, 0));
	}
	if (mtx_len > 6) // presencia de siete comandos (seis pipes)
	{
		cmd_name = ft_split(cmd_pipe[6], ' ');
		ft_cmdadd_back(data, ft_cmd_new(data, cmd_name, 0));
	}
	ft_freedom(cmd_pipe);
}
