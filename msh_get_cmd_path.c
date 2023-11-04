/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_get_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:25:41 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/04 17:37:30 by roruiz-v         ###   ########.fr       */
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
void	ft_find_cmd_path(t_cmd_lst *cmd, char **paths)
{
	int		i;
	char	*path;

	i = -1;
	if (ft_strchr(cmd->path_cmd, '/'))
	{
		cmd->env_path = ft_strdup(cmd->path_cmd);
		printf("*** DEBUG: ft_find_cmd_path) hago strdup\n");
	}
	else
	{
		while (paths[++i])
		{
			path = ft_strjoin(paths[i], "/");
			cmd->env_path = ft_strjoin(path, cmd->path_cmd);
			ft_free_null(path);
			if (access(cmd->env_path, F_OK) == 0)
				break;
			else
				ft_free_null(cmd->env_path);		
		}		
	}
	printf("*** DEBUG: ft_find_cmd_path) env_path = %s\n", cmd->env_path);
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
			ft_printf("PATHS:\n");
			paths = ft_split(tmp->val, ':');
			while (paths[++i])
			{
				ft_printf("*** %s\n", paths[i]);
			}
			break ;		
		}
		tmp = tmp->nx;
	}
	return (paths);
}
