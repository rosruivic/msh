/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:59:38 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/19 19:24:40 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief    BEWARE OF THIS !!!!
 * 	      (BEWARE THIS: the '=' caracter is not stored
 *                      THEN, is handed printed here)
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
//		else
//			ft_printf("%s\n", ptr->nm);			
		ptr = ptr->nx;
	}
}

/**
 * @brief    BEWARE OF THIS !!!!   		*******  FALTA QUE ORDENE ALFABÉTICAMENTE  *******
 * 	      (BEWARE THIS: the '=' caracter is not stored
 *                      THEN, is handed printed here)
 * 
 *  ***   IT IS CALLED BY COMMAND "EXPORT" (without argmts)  ***
 * 	***      Prints all the nodes, in alphabetical order     ***
 */
void	ft_export_lst_print(void)
{
	t_env_lst *ptr;

	ptr = g_data.env_lst;
	while (ptr != NULL)
	{
		if (ptr->equal)
			ft_printf("declare -x %s=\"%s\"\n", ptr->nm, ptr->val);
		else
			ft_printf("declare -x %s\n", ptr->nm);
		ptr = ptr->nx;
	}
}


