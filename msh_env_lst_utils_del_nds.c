/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils_del_nds.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:35:44 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/24 19:57:52 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_envlst_node(t_env_lst *del_node)
{
	ft_free_null(del_node->nm);
	ft_free_null(del_node->val);
	free(del_node);
	del_node = NULL;
}

int	ft_env_check_end_equal(char *del_nd)
{
	if (del_nd && del_nd[ft_strlen(del_nd) - 1] == '=')
	{
		ft_printf("msh: unset: `%s': not a valid identifier\n", del_nd);
		ft_free_null(del_nd); // PODRÍA SER LIBERADO EN OTRO LUGAR MÁS PROPICIO
		return (1);
	}
	return (0);
}

/**
 * @brief   Deletes the node that cointains  (->nm == del_nd)
 * 
 *          *** 	IT WILL BE CALLED BY COMMAND "unset"   ***
 * 
 *  BEWARE OF THIS -> prints an error msg if the last character is an '='
 *  BEWARE OF THIS -> where will be better to liberate [del_nd] string
 * 
 * @param del_nd   The ->nm string to find in the list
 */
void	ft_env_lstdelone(char *del_nd)
{
	t_env_lst	*t;    // tmp node to keep the prev node to the one to be deleted
	t_env_lst	*del;  // finded node to be deleted

	if (ft_env_check_end_equal(del_nd))
		return ;
	if (g_data.env_lst && del_nd)
	{
		t = g_data.env_lst;
		if (!ft_str_equal(t->nm, del_nd))
		{
			while (t->nx != NULL && !ft_str_equal(t->nx->nm, del_nd))
				t = t->nx;
			if (t->nx == NULL)
			{
				ft_free_null(del_nd); // PODRÍA SER LIBERADO EN OTRO LUGAR MÁS PROPICIO
				return ;
			}
		}
		else // coincide el primer nodo, borrar el primer nodo
		{
			g_data.env_lst = t->nx;
			ft_free_envlst_node(t);
			ft_free_null(del_nd); // PODRÍA SER LIBERADO EN OTRO LUGAR MÁS PROPICIO
			return ;
		}
		// finded one equiv after 1st node: building a bridge & deleting node
		del = t->nx;
		t->nx = t->nx->nx;
		ft_free_envlst_node(del);
		ft_free_null(del_nd); // PODRÍA SER LIBERADO EN OTRO LUGAR MÁS PROPICIO
	}		
}

/**
 * @brief   Deletes the complete environment vars list
 *  
 */
void	ft_env_lstclear(t_env_lst *del_lst)
{
	t_env_lst	*del_node;

	if (del_lst == NULL)
		return ;
	while (del_lst)
	{
		del_node = del_lst;
		del_lst = del_node->nx;
		ft_free_envlst_node(del_node);
	}
	ft_printf("DEBUG: lstclear - borrados todos los nodos\n\n");
}
