/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils_print_nds.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:59:38 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/20 21:20:43 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief    BEWARE OF THIS !!!! 
 * 	      (BEWARE OF THIS: the '=' caracter is not stored
 *                      THEN, is hand printed here)
 * 
 *  ***  IT IS CALLED BY COMMAND "ENV" (without argmts)  ***
 * 	***    Only prints the node if its ->val != NULL     ***
 */
void	ft_env_lst_print(void)
{
	t_env_lst *ptr;

	ptr = g_data.env_lst;
	while (ptr != NULL)
	{
		if (ptr->equal)
			ft_printf("%s=%s\n", ptr->nm, ptr->val);			
		ptr = ptr->nx;
	}
}

/**
 * @brief    BEWARE OF THIS !!!!  *******  FALTA QUE ORDENE asciiMENTE  *******
 * 	      (BEWARE OF THIS: the '=' caracter is not stored
 *         THEN, is hand printed here, AS THE "" CHARACTERS TO PRINT VALUE)
 * 
 *  ***   IT IS CALLED BY COMMAND "EXPORT" (without argmts)  ***
 * 	***         Prints all the nodes, in ascii order         ***
 */
void	ft_export_lst_print(void)
{
	t_env_lst *ptr;

//	ptr = g_data.env_lst; // Y ESTO NO HAY QUE LIBERARLO EN NINGÚN MOMENTO ????
	ptr = ft_env_lst_ascii_order();
	while (ptr != NULL)
	{
		if (ptr->equal)
			ft_printf("declare -x %s=\"%s\"\n", ptr->nm, ptr->val);
		else
			ft_printf("declare -x %s\n", ptr->nm);
		ptr = ptr->nx;
	}
}


