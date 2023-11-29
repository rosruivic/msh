/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_executor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:21:55 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/29 19:27:13 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redir_checker(t_msh *data, t_cmd_lst *cmd_nd)
{
	if (data->cmd_lst->rds != NULL && data->cmd_lst->rds->type == DIR)
	{
		ft_heredoc(data, cmd_nd);
	}
	else if (data->cmd_lst->rds != NULL && data->cmd_lst->rds->type == SIR)
	{
		//printf("DEBUG: ft_redir_checker) aún no hago nada - SIR\n");
		ft_redir_infile(data, cmd_nd);
	}
	else if (data->cmd_lst->rds != NULL && data->cmd_lst->rds->type == SOR)
		printf("DEBUG: ft_redir_checker) aún no hago nada - SOR\n");
	else if (data->cmd_lst->rds != NULL && data->cmd_lst->rds->type == DOR)
		printf("DEBUG: ft_redir_checker) aún no hago nada - DOR\n");
}

/**
 * @brief ** Checks if the cmd is a builtin or an external command **
 * 	>> env    -> bash admits both LOWERS & UPPERS
 *  >> export -> bash admits only LOWERS, not UPPERS
 *  >> unset  -> bash admits only LOWERS, not UPPERS
 *  >> pwd    -> bash admits both LOWERS & UPPERS
 *  >> cd     -> bash admits both LOWERS & UPPERS (but do nothing if UPPERS)
 *  >> echo   -> bash admits both LOWERS & UPPERS
 *  >> exit   -> bash admits only LOWERS, not UPPERS
 * 
 *  BEWARE OF THIS !!! >>> In case of absolute path, 
 * 		¿¿¿ what should be executed, the REAL builtin or ours ???
 * 	ANSWER >>> the builtins don't have absolute path, 
 *             they comunicate to the shell directly
 * 
 * 	VERSIÓN 1.0 --> VÁLIDO PARA UN SOLO COMANDO
 * 
 * @param data 
 * @param cmd 
 */
/* void	ft_builtin_executor(t_msh *data, char *cmd)
{	
	ft_redir_checker(data);
	if (ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "ENV") == 0)
		ft_builtin_exec_env(data);
	else if (ft_strcmp(cmd, "export") == 0)
		ft_builtin_exec_export(data);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_builtin_exec_unset(data);
	else if (ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "PWD") == 0)
		ft_builtin_exec_pwd(data);
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_builtin_exec_cd(data);
	else if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "ECHO") == 0)
		ft_builtin_exec_echo(data);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_builtin_exec_exit(data);
	else
	{
		ft_find_cmd_path(data->cmd_lst, ft_find_env_paths(data));
		data->exit_code = ft_exec_external_cmd(data);
	}
} */

/**
 * @brief   ** VERSIÓN 2.0 -> PASANDO UN NODO (PRESENCIA DE PIPES)
 * 				*** UNDER CONSTRUCTION, AÚN NO HACE ESO ***
 * @param data 
 * @param cmd 
 * @param tmp 
 */
void	ft_builtin_executor(t_msh *data, char *cmd, t_cmd_lst *cmd_nd)
{
	if (data->cmd_lst->rds != NULL)
	{
		ft_redir_checker(data, cmd_nd);
		if (data->exit_code == EXIT_FAILURE)
			return ;
	}
	if (ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "ENV") == 0)
		ft_builtin_exec_env(data);
	else if (ft_strcmp(cmd, "export") == 0)
		ft_builtin_exec_export(data);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_builtin_exec_unset(data);
	else if (ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "PWD") == 0)
		ft_builtin_exec_pwd(data);
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_builtin_exec_cd(data);
	else if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "ECHO") == 0)
		ft_builtin_exec_echo(data);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_builtin_exec_exit(data);
	else
	{
		ft_find_cmd_path(cmd_nd, ft_find_env_paths(data));
		data->exit_code = ft_exec_external_cmd(data);
	}
}
