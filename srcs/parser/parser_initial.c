#include "../../include/parser.h"

t_par_list	*par_initial_empty_list(void)
{
	t_par_list	*new; // no new!!!

	new = (t_par_list *)malloc(sizeof(t_par_list));
	if (!new)
		return (NULL);
	new->size = 0;
	new->begin = NULL;
	new->end = NULL;
	return (new);
}

char	**par_get_redirect(void)
{
	char	*rediret_arr[10]; //??????

	// rediret_arr = (char **)malloc(sizeof(char *) * 6);
	if (!rediret_arr)
		return (NULL);
	rediret_arr[0] = "<\0";
	rediret_arr[1] = ">\0";
	rediret_arr[2] = "<<\0";
	rediret_arr[3] = ">>\0";
	rediret_arr[4] = "|\0";
	rediret_arr[5] = NULL;
	return (rediret_arr);
}


t_par_elem	*par_get_new_elem(int type, char *value)
{
	t_par_elem	*new_elem;

	new_elem = (t_par_elem *)malloc(sizeof(t_par_elem));
	if (!new_elem || !value)
		return (NULL);
	new_elem->type = type;
	new_elem->value = value;
	new_elem->prev = NULL;
	new_elem->next = NULL;
	return (new_elem);
}
