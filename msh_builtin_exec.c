/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:21:55 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/30 20:27:53 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_exec_exit(t_msh *data)
{
//	ft_free_all(data);
	ft_env_lstclear(data->env_lst);
//	ft_cmd_lstclear(data->cmd_lst);
	exit (END);
}

void	ft_builtin_exec_env(t_msh *data)
{
	ft_env_lst_print(data);
}

void	ft_builtin_exec_export(t_msh *data)
{
	ft_export_lst_print(data);
}

void	ft_builtin_exec_unset(t_msh *data)
{
	ft_env_lstdelone(data, data->env_lst->nm);
}

void	ft_builtin_exec_pwd(t_msh *data)
{
	(void)data;
	ft_printf("*** DEBUG: estoy en ft_builtin_exec_pwd\n");
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
