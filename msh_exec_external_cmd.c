/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_external_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:15:50 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/06 17:35:39 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_lst_count_nds(t_env_lst *env_lst)
{ // FUNCIONA BIEN - OK
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
	int			nb_env;

	i = 0;
	my_envp = NULL;
	nb_env = ft_env_lst_count_nds(data->env_lst);
	tmp = data->env_lst;
	my_envp = ft_calloc(nb_env + 1, sizeof(char *));
	while (tmp != NULL)
	{
		my_envp[i] = ft_strdup(tmp->nm);
		if (tmp->equal)
		{
			my_envp[i] = ft_join_free(my_envp[i], "=");
			my_envp[i] = ft_join_free(my_envp[i], tmp->val);
		}
		tmp = tmp->nx;
		i++;
	}
	return (my_envp);
}

int	ft_exec_external_cmd(t_msh *data)
{
	int		exit_code;
	char	**my_envp;
	
	printf("data->cmd_lst->args[0] => %s\n", data->cmd_lst->args[0]);
	my_envp = ft_conv_envlst_to_mtrx(data);
	data->cmd_lst->pid = fork();
	if (data->cmd_lst->pid == -1)
		ft_error_status(data, ERROR_PID);
	if (data->cmd_lst->pid == 0) // is the child
	{
		execve(data->cmd_lst->env_path, data->cmd_lst->args, my_envp);
		ft_error_status(data, ERROR_CMD_NOT_EXISTS);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(data->cmd_lst->pid, &exit_code, 0);
	//	ft_actualize_envlst(data, my_envp); // HAY QUE IMPLEMENTARLA
	//	printf("\n\n\n*** DEBUG: ft_exec_external_cmd) WEXITSTATUS => %d\n", exit_code);
	}
	ft_freedom(my_envp);
	return (WEXITSTATUS(exit_code));		
//		ft_free_cmd_lst(&data); // HAY QUE IMPLEMENTARLA (= free_env_lst)
}
