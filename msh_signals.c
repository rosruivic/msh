/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:00:34 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/29 18:13:23 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   **  ONLY CHECKS CTRL+C, NOT CTRL+\ (TO IGNORE) **
 * 
 * @param sig 
 * @param info 
 * @param context 
 */
void	ft_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (isatty(STDIN_FILENO))
	{ //       printf("STDIN is the terminal.\n");
		if (SIGINT == sig)
		{
			g_listen = 1;
			rl_on_new_line();
			rl_redisplay();
			rl_replace_line("", 0);		// gcc error C99 (INSTALL LIBRARY)
			ft_putstr_fd("   \n", 1);
			rl_on_new_line();
			rl_redisplay();
		}
    }
	else // printf("STDIN is redirected.\n");
	{
        if (SIGINT == sig)
		{
			g_listen = 1;
			ioctl(0, TIOCSTI, "\n"); // añade un intro a lo bestia
			rl_on_new_line();
//			rl_redisplay();
			rl_replace_line("", 0);		// gcc error C99 (INSTALL LIBRARY)
//			rl_on_new_line();
			rl_redisplay();
		}
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
			rl_clear_history();		// gcc error C99 (INSTALL LIBRARY)
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
