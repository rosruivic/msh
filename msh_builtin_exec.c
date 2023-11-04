/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:21:55 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/04 18:11:57 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief    ****  BEWARE OF THIS !!! ******
 * 		MUST RETURN AN EXIT VALUE, DEPENDING ON SOME FACTS
 * 
 * @param data 
 */
void	ft_builtin_exec_exit(t_msh *data) // CTRL+D activates this ft
{
	ft_error_status(data, END);
	ft_env_lstclear(data->env_lst);
	exit(0);
}

/**
 * @brief      ********   READY !!!!   ********
 * 
 * @param data 
 */
void	ft_builtin_exec_env(t_msh *data)
{
	ft_env_lst_print(data);
}

void	ft_builtin_exec_export(t_msh *data)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	if (ft_matrix_len(data->cmd_lst->args) == 1)
		ft_export_lst_print(data);
	else
	{
		while (data->cmd_lst->args[++i])
		{ // obtengo la matriz que separa el name del value de la env var
			tmp = ft_2rows_split(data->cmd_lst->args[i], '=');
			if (ft_strchr(data->cmd_lst->args[i], '='))
				ft_env_modify_or_add_node(data, ft_env_lst_new(tmp, 1));
			else
				ft_env_modify_or_add_node(data, ft_env_lst_new(tmp, 0));
			ft_freedom(tmp);
		}
	}
}

void	ft_builtin_exec_unset(t_msh *data)
{
	int	i;

	i = 0;
	while (data->cmd_lst->args[++i])
		ft_env_lstdelone(data, data->cmd_lst->args[i]);
}

void	ft_builtin_exec_pwd(t_msh *data)
{
	char	*cwd;
	
	(void)data;
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, data->fd);
	ft_putchar_fd('\n', data->fd);
	ft_free_null(cwd);
}

void	ft_builtin_exec_cd(t_msh *data)
{
	(void)data;
	ft_printf("*** DEBUG: estoy en ft_builtin_exec_cd\n");
}

void	ft_builtin_exec_echo(t_msh *data)
{
	(void)data;
	ft_printf("*** DEBUG: estoy en ft_builtin_exec_echo\n");
}

void	ft_builtin_exec(t_msh *data, char *cmd)
{
	if (ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "ENV") == 0)
		ft_builtin_exec_env(data);
	else if (ft_strcmp(cmd, "export") == 0) // bash no accepts UPPERS
		ft_builtin_exec_export(data);
	else if (ft_strcmp(cmd, "unset") == 0) // bash no accepts UPPERS
		ft_builtin_exec_unset(data);
	else if (ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "PWD") == 0)
		ft_builtin_exec_pwd(data);
	else if (ft_strcmp(cmd, "cd") == 0) // bash accepts UPPERS, but do nothing
		ft_builtin_exec_cd(data);
	else if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "ECHO") == 0)
		ft_builtin_exec_exit(data);
	else if (ft_strcmp(cmd, "exit") == 0) // bash no accepts UPPERS
		ft_builtin_exec_exit(data);
	else
	{
		ft_printf("******** DEBUG: NO ES NINGÚN BUILTIN\n");
		ft_find_cmd_path(data->cmd_lst, ft_find_env_paths(data));
//		ft_exec_external_cmd(data, cmd);
	}
}
