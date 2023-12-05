/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:00:34 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/05 01:53:08 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   **  ONLY CHECKS CTRL+C, NOT CTRL+\ (TO IGNORE) **
 *  Cuando nuestro shell recibe una señal SIGINT, el comportamiento por defecto
 * es terminar el proceso. Para cambiar este comportamiento, podemos establecer
 * un manejador de señales para SIGINT. Un manejador de señales es una función
 * que se ejecuta cuando se recibe una señal. Para establecer un manejador de
 * señales, usamos la función sigaction. Lo que pretendemos con esta función es
 * que nuestro shell ignore la señal SIGINT, para que no termine la ejecución
 * del programa sino que, simplemente, se quede esperando una nueva entrada del
 * usuario.
 * 
 *  La función isatty se usa para saber si la entrada estándar es un terminal.
 * La función isatty devuelve 1 si el descriptor de fichero que le pasamos
 * corresponde a un terminal, y 0 si no. Si el descriptor de fichero es 0, se
 * refiere a la entrada estándar (stdin). Por lo tanto, si el resultado de
 * isatty es 1, significa que la entrada estándar es un terminal, y si es 0,
 * significa que la entrada estándar no es un terminal, es decir, que la
 * entrada estándar está redirigida desde un fichero o desde la salida de otro
 * programa.
 * 
 *  La función ioctl se usa para controlar dispositivos. En este caso, la
 * función ioctl se usa para controlar la entrada estándar.
 * 	La función ioctl recibe tres argumentos: 
 * - el descriptor de fichero,
 * - el comando que queremos ejecutar 
 * - y un puntero a una estructura de datos (por ejemplo, un puntero a un
 *  carácter, un puntero a un entero, etc.).
 * En este caso, el comando que queremos ejecutar es TIOCSTI, que significa
 * "Terminal Input Output Control STdIn".
 * Este comando se usa para insertar un carácter en la entrada estándar. El
 * puntero a la estructura es un puntero a un carácter, que es el carácter que
 * queremos insertar en la entrada estándar. En este caso, el carácter que
 * queremos insertar es un salto de línea, que es el carácter '\n'.
 * 
 * 
 * @param sig 
 * @param info 
 * @param context 
 */
void	ft_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (SIGINT == sig) // user press CTRL+C
	{
		if (isatty(STDIN_FILENO))
		{ 	// printf("STDIN is the terminal.\n");

			printf("DEBUG: this is HANDLER_PARENT because the user is introducing a pipeline\n");
			g_listen = 1;
			rl_on_new_line();
			rl_redisplay();
//			rl_replace_line("", 0);		// gcc error C99 (INSTALL LIBRARY at home)
			ft_putstr_fd("   \n", 1);
			rl_on_new_line();
			rl_redisplay();
		}
		else // printf("STDIN is redirected.\n");
		{
			printf("DEBUG: this is HANDLER_CHILD because the user is in a redirection (piped heredoc)\n");
			g_listen = 1;
			rl_on_new_line();
//			rl_redisplay();
//			rl_replace_line("", 0);		// gcc error C99 (INSTALL LIBRARY at home)
//			rl_on_new_line();
			rl_redisplay();
//			ioctl(0, TIOCSTI, '\n'); // añade un intro a lo bestia (no hace nada)
//			exit(EXIT_FAILURE); 	// si lo pongo aquí, me saca de minishell
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
