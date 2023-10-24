/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils_ascii_order.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:58:21 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/24 20:56:31 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief        **** NO FUNCIONA EN ABSOLUTO  ****
 * 
 * @param cpy_lst 
 * @return t_env_lst* 
 */
t_env_lst	*ft_order_lst(t_env_lst *cpy_lst)
{
	t_env_lst	*current; // nodo actual
	t_env_lst	*index;   // nodo siguiente
	t_env_lst	*tmp;
	
	current = cpy_lst;
	index = NULL;
	while (current != NULL) // vamos a pasar por todos los nodos una sola vez
	{
		index = current->nx; // el nodo siguiente al actual
		while (index != NULL)
		{
			if (ft_strcmp(index->nm, index->nx->nm) > 0)
			{ // los intercambio:
				tmp = current;    // tmp señala al actual
				current = index;  // actual señala al siguiente
				index = tmp;      // el siguiente señala al tmp (al actual)
			}
			else if (ft_strcmp(current->nm, index->nm) == 0 && current->equal)
			{
				if (ft_strcmp(current->val, index->val) > 0)
				{
					tmp = current;
					current = index;
					index = tmp;					
				}
			}
			index = index->nx;
		}
		current = current->nx;
	}
	return (index);
}

/**
 * @brief    ***** UNDER CONSTRUCTION *****
 * 
 * @return t_env_lst* 
 */
t_env_lst	*ft_env_lst_ascii_order(void)
{
//	t_env_lst	*cpy_lst;
	t_env_lst	*src;

	src = g_data.env_lst;
//	cpy_lst = ft_duplic_lst(src);
	return (ft_order_lst(src));
//	return (ft_order_lst(cpy_lst));
}


