/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:17:18 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/13 20:59:24 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_both_linked_lists(t_msh *data)
{
	ft_cmd_lstclear(data);
	ft_env_lstclear(data->env_lst);
}

/**
 * @brief   ** RETURNS AN EXIT VALUE that DEPENDS ON SOME FACTS **
 * BEWARE OR THIS !!! >> 
 *    Don't alterate the following order {'if / if else'}'s chain,
 *       (it's deeply thought to show the correct messages)
 * 
 * @param data 
 */
void	ft_builtin_exit(t_msh *data)
{
	ft_putstr_fd(data->cmd_lst->c_args[0], 1);
	ft_putchar_fd('\n', 1);
	if (ft_matrix_len(data->cmd_lst->c_args) > 1
		&& (!ft_is_str_digits(data->cmd_lst->c_args[1])))
	{
		ft_putstr_fd("msh: exit: ", 2);
		ft_putstr_fd(data->cmd_lst->c_args[1], 2);		
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_free_both_linked_lists(data);
		exit(255);
	}
	else if (ft_matrix_len(data->cmd_lst->c_args) > 2)
		ft_error_status(data, ERROR_TOO_MANY_ARGUMENTS);
	else if (ft_matrix_len(data->cmd_lst->c_args) == 2
		&& ft_is_str_digits(data->cmd_lst->c_args[1]))
	{
		ft_env_lstclear(data->env_lst);
		exit(ft_atoi(data->cmd_lst->c_args[1]));
	}
	else // exit sin argumentos
	{
		ft_free_both_linked_lists(data);
		exit(0);
	}
}
