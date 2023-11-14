/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:00:34 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/14 16:52:45 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (SIGINT == sig)
	{
		g_listen = 1;
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		ft_putstr_fd("   \n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
 * @brief   **   A MEDIAS (FALTA LIBERAR Y QUITAR EL '^D')
 * 
 * @param pipeline 
 */
void	ft_ctrl_d(t_msh *data)
{
	if (!data->pipeline)
	{
		rl_on_new_line(); // parece que limpia el búffer
		rl_redisplay();	// y parece que se pone al inicio de la misma línea
		ft_putstr_fd("exit\n", 1);
		rl_clear_history();
		ft_env_lstclear(data->env_lst);
		exit(EXIT_SUCCESS);
	}
}

/* void	ft_ctrl_c(t_msh *data)
{
	
} */
