/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:06:56 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/30 17:53:04 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* need to name the head of list which is pointed by **lst */

void	ft_lstadd_back(t_msh *data, t_list *new)
{
	t_list	*temp;

	temp = NULL;
	if (*lst == NULL && new)
		*lst = new;
	else if (*lst && new)
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}
