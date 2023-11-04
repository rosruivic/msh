/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_external_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:15:50 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/04 20:07:40 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_env_lst_count_nds(t_env_lst *env_lst)
{
	int	elmts;
	t_env_lst *tmp;

	elmts = 0;
	tmp = env_lst;
	while (tmp != NULL)
	{
		elmts++;
		tmp = tmp->nx;
	}
	return (elmts);
}

static char	**ft_conv_envlst_to_mtrx(t_msh	*data)
{
	char		**my_envp;
	t_env_lst	*tmp;
	int			i;

	i = -1;
	my_envp = NULL;
	tmp = data->env_lst;
	while (tmp != NULL)
	{
		my_envp = ft_calloc(ft_env_lst_count_nds(data->env_lst) + 1,
			sizeof(t_env_lst));
		while (i++ < ft_env_lst_count_nds(data->env_lst))
		{
			if (tmp->equal)
				my_envp[i] = ft_strjoin(tmp->nm, '=');
			my_envp[i] = ft_strjoin(my_envp, tmp->val);
			ft_printf(" **** DEBUG: ft_conv_envlst_to_mtrx) %s\n", my_envp[i]);
		}
	}
	return (my_envp);
}

static int	ft_forks(t_msh *data, char **my_envp)
{
	int	exit_code;
	
	data->cmd_lst->pid = fork();
	if (data->cmd_lst->pid == 0) // is the child
	{
//		dup2(data->fd[0], STDIN_FILENO);
		execve(data->cmd_lst->path_cmd, data->cmd_lst->args, 
			ft_conv_envlst_to_mtrx(data));
		ft_errors(data, ERROR_CMD_NOT_EXISTS);
	}
//		ft_free_cmd_lst(&data); // HAY QUE IMPLEMENTARLA (= free_env_lst)
}

void	ft_exec_external_cmd(t_msh *data, t_cmd_lst cmd)
{
	ft_forks(data, ft_conv_envlst_to_mtrx(data));
	
}
