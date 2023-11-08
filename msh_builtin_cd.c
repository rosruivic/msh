/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:26:32 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/08 20:29:09 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_env_obtain_env_val(t_msh *data, char *str)
{
	char		*pwd_val;
	t_env_lst	*tmp;
	
	tmp = data->env_lst;
	if (!str)
		return (NULL);
	if (tmp != NULL && ft_strcmp(tmp->nm, str) == 0)
	{
		
	}
	
	return (pwd_val);
}

static void	ft_env_change_env_val(t_msh *data, char *str)
{
	t_env_lst	*tmp;

	tmp = data->env_lst;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->nm, str) == 0)
		{
			ft_free_null_void_return(&tmp->val);
			tmp->val = ft_obtain_pwd_val(data, "PWD");
		}
		else
			tmp = tmp->nx;
	}
}


/**
 * @brief       *** UNDER CONSTRUCTION ***
 * 
 *  >> cd .  --> do NOTHING & print NOTHING
 *  >> cd .. --> chdir to ONE_LEVEL_UP
 * 	>> cd    --> chdir to HOME (/Users/roruiz-v)
 *  >> cd ~  --> chdir to HOME (/Users/roruiz-v)
 *  >> cd -  --> chdir to OLDPWD (& prints the path)
 *  >> cd /  --> chdir to ROOT
 *  >> cd algo otracosa  --> treat the 1st argmt, ignore the rest
 * 
 * @param data 
 */
void	ft_builtin_exec_cd(t_msh *data)
{	
	char	*pwd;
	
	pwd = NULL;
	if (data->cmd_lst->c_args[1])
	{
		if (chdir(data->cmd_lst->c_args[1]) == 0)
		{
			ft_env_change_env_val(data, "OLDPWD", pwd);
			ft_env_change_env_val(data, "PWD", getcwd(NULL, 0));
			printf("DEBUG: builtin ) el chdir ha ido bien\n");
		}
		else
			ft_error_status(data, ERROR_CHDIR_FAILURE);
	}
}