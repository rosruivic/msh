#include "minishell.h"

static void	ft_env_mfy_or_add_nd(t_env_lst *new);
void	ft_env_exchange_val(t_env_lst *t_nd, t_env_lst *new);
void	ft_env_join_val(t_env_lst *t_nd, t_env_lst *new);

void	ft_env_modify_or_add_node(t_env_lst *new)
{
	if (!new)
		return ;
	if (g_data.env_lst == NULL)
		g_data.env_lst = new;
	else
		ft_env_mfy_or_add_nd(new);
}

static void	ft_env_mfy_or_add_nd(t_env_lst *new)
{// 'new->val' llega SIN COMILLAS (naturalmente, es un string)
	t_env_lst	*t;

	t = g_data.env_lst;
	if (ft_str_equal(t->nm, new->nm)) // encuentra coincidencia en primer nodo
	{
		if (new->nm[0] != '$') 
			ft_env_exchange_val(t, new); // cambia 'val', equal = 1 si procede, freenode
		else // strjoin lo que había + lo nuevo
			ft_env_join_val(t, new); // en dicha función se liberará new
	}
	else // no hubo coincidencia en el primer nodo, repasamos los demás
	{
		while (!ft_str_equal(t->nx->nm, new->nm) && t->nx->nx != NULL)
			t = t->nx;
		if (t->nx->nx == NULL) // no ha habido coincidencias, new se añade al final
			t->nx->nx = new;
		else // ha habido coincidencia en un nodo, hay que cambiar value
		{
			if (new->nm[0] != '$') 
				ft_env_exchange_val(t->nx, new); // equal = 1 si procede, free new
			else // strjoin lo que había + lo nuevo
				ft_env_join_val(t->nx, new); // free new
		}
	}
}

void	ft_env_exchange_val(t_env_lst *t_nd, t_env_lst *new)
{
	ft_free_null(t_nd->val);
	t_nd->val = ft_strdup(new->val);
	if (t_nd->equal == 0) // si ya estaba en 1, no puede cambiar a 0
		t_nd->equal = new->equal;
	ft_free_envlst_node(new);
}

void	ft_env_join_val(t_env_lst *t_nd, t_env_lst *new)
{
	t_nd->val = ft_join_free(t_nd->val, new->val);
	if (t_nd->equal == 0) // si ya estaba en 1, no puede cambiar a 0
		t_nd->equal = new->equal;
	ft_free_envlst_node(new);
}

