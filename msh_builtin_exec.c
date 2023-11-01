/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:21:55 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/01 21:07:54 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief    ****  BEWARE OF THIS !!! ******
 * 		MUST RETURN AN EXIT VALUE, DEPENDING ON SOME FACTS
 * 
 * @param data 
 */
void	ft_builtin_exec_exit(t_msh *data)
{
	ft_error_status(data, END);
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
	ft_env_lstdelone(data, data->env_lst->nm);
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

void	ft_builtin_exec(t_msh *data, char *cmd)
{
	if (ft_strcmp(cmd, "env") == 0)
		ft_builtin_exec_env(data);
	else if (ft_strcmp(cmd, "export") == 0)
		ft_builtin_exec_export(data);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_builtin_exec_unset(data);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_builtin_exec_pwd(data);
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_builtin_exec_cd(data);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_builtin_exec_exit(data);
	else
		ft_printf("*** DEBUG: NO ES NINGÚN BUILTIN\n");
}
