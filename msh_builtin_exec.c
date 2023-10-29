/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:21:55 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/29 18:46:39 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_exec_exit(t_msh *data)
{
//	ft_free_all(data);
	ft_free_envlst_node(data->env_lst);
	ft_free_envlst_node(data->cmd_lst);
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

ft_builting_exec(t_msh *data, char *cmd)
{
	if (cmd == "env")
		ft_builtin_exec_env(data);
	else if (cmd == "export")
		ft_builtin_exec_export(data);
	else if (cmd == "unset")
		ft_builtin_exec_unset(data);
	else if (cmd == "pwd")
		ft_builtin_exec_pwd(data);
	else if (cmd == "cd")
		ft_builtin_exec_cd(data);
	else if (cmd == "exit")
		ft_builtin_exec_exit(data);
}
