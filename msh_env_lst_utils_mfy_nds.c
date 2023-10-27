#include "minishell.h"

/**             ***   PENDIENTE DE REESCRIBIR    ***
 *    (AÑADIR CASO '$' (STRJOIN) Y DIVIDIR EN FUNCIONES MÁS CORTAS)
 * 
 * @brief  
 *      IF THE NEW NODE ALREADY EXISTS (->nm), then:
 * 	    	- delete & free old (->val)
 *          - && malloc & strdup new (->val) or strjoin ('$')
 * 			- delete the new node (cause it's not new anymore)
 * 		ELSE:
 * 		    - lstadd_back the new node
 * 
 * @param new     Node to be added || modified
 */
void	ft_env_modify_or_add_node(t_env_lst	*new)
{
	t_env_lst	*t;

	t = NULL;
	if (g_data.env_lst == NULL && new)
	{
		g_data.env_lst = new;
		return ;
	}
	if (g_data.env_lst && new)
	{
		t = g_data.env_lst;
		if (!ft_str_equal(t->nm, new->nm)) // CHECK THE FIRST NODE
		{// if no equiv, check the next nodes:
			while (!ft_str_equal(t->nx->nm, new->nm))
			{ // GO AHEAD'til find equiv;
				if (t->nx->nx == NULL) // last node with no equiv (add & end)
				{
					t->nx->nx = new;
					return ;
				}
				t = t->nx;
			}
		}
		else // coincide el primer nodo - intercambia los nodos
		{
			g_data.env_lst = t->nx;
			ft_free_envlst_node(t);    // elimina el antiguo
			ft_env_lstadd_front(new);  // lo sustituye el nuevo
			return ;
		}
	}
	// finded equiv intermediate nodo - DELETE OLD STR Y STRDUP NEW ONE
	ft_free_null(t->nx->val);
	t->nx->val = ft_strdup(new->val);
	ft_free_envlst_node(new);
}
