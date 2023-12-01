/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:51:18 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/01 20:22:28 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler_parent(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	
	if (SIGINT == sig)
	{
		printf("HANDLER_PARENT\n");
		g_listen = 1;
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);		// gcc error C99 (INSTALL LIBRARY)
		ft_putstr_fd("   \n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}
void	ft_handler_child(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
    if (SIGINT == sig)
	{
		printf("HANDLER_CHILD\n");
		g_listen = 1;
		rl_on_new_line();
//		rl_redisplay();
		rl_replace_line("", 0);		// gcc error C99 (INSTALL LIBRARY)
//		rl_on_new_line();
		rl_redisplay();
//		ioctl(0, TIOCSTI, "\n"); // añade un intro a lo bestia (pero no hace nada?)
		exit(EXIT_FAILURE); // si lo pongo aquí, me saca de minishell
    }
}

/**
 * @brief    **  IT'S NOT A SIGNAL, ONLY A SPECIAL CHARACTER **
 * 	-	rl_on_new_line(); // parece que limpia el búffer
 *	-	rl_redisplay();	// y parece que se pone al inicio de la misma línea
 * 
 * @param data 
 */
void	ft_ctrl_d(t_msh *data)
{
	if (isatty(STDIN_FILENO))
	{ //       printf("STDIN is the terminal.\n");
		if (!data->pipeline)
		{
			rl_on_new_line();
			rl_redisplay();
			ft_putstr_fd("exit\n", 1);
//			rl_clear_history();		// gcc error C99 (INSTALL LIBRARY)
			ft_env_lstclear(data->env_lst);
			exit(EXIT_SUCCESS);
		}
	}
	else // printf("STDIN is redirected.\n");
	{
		if (!data->pipeline)
		{
//			rl_replace_line("", 0); // si la enchufo, explicar pq´
			rl_on_new_line();		// cursor al principio
			rl_redisplay(); 		// pone el prompt del '>>> msh_2.0$'
			exit(EXIT_SUCCESS);
		}
	}
}
