/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_env_pwd_unset.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:02:24 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/19 20:02:51 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief      ********   READY   ********
 *   
 * @param data 
 */
void	ft_builtin_exec_env(t_msh *data)
{ // OJO - CONTROL DE ARGUMENTOS (DA MENSAJE DE ERROR)
	if (ft_matrix_len(data->cmd_lst->c_args) == 1)
		ft_env_lst_print(data);
	else
		ft_error_status(data, ERROR_NO_SUCH_FILE_OR_DIRECTORY);
}

/**
 * @brief   **  UNSET admits many argmts (many vars to delete)  **
 * 		        so, a boucle 'while' do this
 * 
 * @param data 
 */
void	ft_builtin_exec_unset(t_msh *data)
{ // VERIFICAR EL CÓDIGO DE SALIDA
	int	i;

	i = 0;
	while (data->cmd_lst->c_args[++i])
		ft_env_lstdelone(data, data->cmd_lst->c_args[i]);
}

void	ft_builtin_exec_pwd(t_msh *data)
{ // VERIFICAR EL CÓDIGO DE SALIDA
	char	*cwd;
	
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, data->fd);
	ft_putchar_fd('\n', data->fd);
	ft_free_null_void_return(&cwd);
	data->exit_code = 0;
}
