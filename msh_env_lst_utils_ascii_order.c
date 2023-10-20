/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils_ascii_order.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:58:21 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/20 21:21:57 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief    ***** UNDER CONSTRUCTION *****
 * 
 * @return t_env_lst* 
 */
t_env_lst	*ft_env_lst_ascii_order(void)
{
	t_env_lst	*ord;
	t_env_lst	*src;

	src = g_data.env_lst;
	ord = ft_duplic_lst(src); // para no ordenar la lista original
	if (ft_env_lst_is_order(ord))
		return (ord);
	while (1)
	{
		if (src->nm < src->nx->nm)
			ft_env_lstadd_back(ord);
		if (ft_env_lst_is_order)
			ft_export_print() ;
	}
}
