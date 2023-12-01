/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:00:34 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/01 11:55:09 by roruiz-v         ###   ########.fr       */
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
//			rl_replace_line("", 0);		// gcc error C99 (INSTALL LIBRARY)
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
			rl_on_new_line();
//			rl_redisplay();
//			rl_replace_line("", 0);		// gcc error C99 (INSTALL LIBRARY)
//			rl_on_new_line();
			rl_redisplay();
			ioctl(0, TIOCSTI, "\n"); // añade un intro a lo bestia (no hace nada)
//			exit(EXIT_FAILURE); // si lo pongo aquí, me saca de minishell
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


/* PREGUNTA: como puedo establecer un comportamiento diferente para SIGINT 
según esté en el proceso padre o en el proceso hijo.

RESPUESTA: Puedes establecer diferentes manejadores de señales para el
proceso padre y el proceso hijo. Cuando se crea un proceso hijo con fork,
el hijo hereda las señales del padre, pero cualquier cambio que haga el
hijo a los manejadores de señales después de la llamada a fork no afectará
al padre.

Aquí hay un ejemplo de cómo podrías hacer esto:

		void handle_sigint_parent(int sig) 
		{
		    // Comportamiento del padre al recibir SIGINT
		}
		
		void handle_sigint_child(int sig) 
		{
		    // Comportamiento del hijo al recibir SIGINT
		}
		
		int main() 
		{
		    // Establece el manejador de señales para el padre
		    signal(SIGINT, handle_sigint_parent);
		
		    pid_t pid = fork();
		    if (pid == 0) {
		        // Estamos en el proceso hijo
		        // Establece el manejador de señales para el hijo
		        signal(SIGINT, handle_sigint_child);
		        // El resto del código del hijo va aquí
		    } else if (pid > 0) {
		        // Estamos en el proceso padre
		        // El manejador de señales ya está establecido
		        // El resto del código del padre va aquí
		    } else {
		        // Hubo un error al crear el proceso hijo
		        perror("fork");
		        exit(EXIT_FAILURE);
		    }
		}

En este código, handle_sigint_parent es el manejador de señales para
el proceso padre y handle_sigint_child es el manejador de señales para
el proceso hijo. En main, primero se establece el manejador de señales
para el padre. Luego, después de la llamada a fork, el hijo establece
su propio manejador de señales. */
