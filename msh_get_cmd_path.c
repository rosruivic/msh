/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_get_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:25:41 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/17 12:55:47 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * @brief     *** BEWARE OF THIS !!!! ***
 * 		First check if the command has an absolute direction.
 * 		If it has it, then only do ft_strdup, that's all.
 * 
 * @param cmd 
 * @param paths 
 */
void	ft_find_cmd_path(t_cmd *cmd_nd, char **paths)
{
	int		i;
	char	*path;

	i = -1;
	if (!paths)
//		ft_error_status(cmd_nd->orgn, cmd_nd, ERROR_NO_PATHS);
		cmd_nd->c_env_path = ft_strdup(cmd_nd->c_abs_path); // PROBANDO
	else if (ft_strchr(cmd_nd->c_abs_path, '/'))
		cmd_nd->c_env_path = ft_strdup(cmd_nd->c_abs_path);
	else
	{
		while (paths[++i])
		{
			path = ft_strjoin(paths[i], "/");
			cmd_nd->c_env_path = ft_strjoin(path, cmd_nd->c_abs_path);
			ft_free_null_void_return(&path);
			if (access(cmd_nd->c_env_path, F_OK) == 0)
				break;
			else
				ft_free_null_void_return(&cmd_nd->c_env_path);		
		}		
	}
	ft_freedom(paths);
}

/**
 * @brief ***** VER LA IMPLEMENTACIÓN DEL PIPEX  *****
 * 
 * @param data 
 * @param cmd 
 */
char	**ft_find_env_paths(t_msh *data)
{
	char		**paths;
	t_env_lst	*tmp;
	int			i;

	i = -1;
	paths = NULL;
	tmp = data->env_lst;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->nm, "PATH") == 0)
		{
			paths = ft_split(tmp->val, ':');
			break ;		
		}
		tmp = tmp->nx;
	}
	return (paths);
}
