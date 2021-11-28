#include "../../include/parser.h"

int	par_push_back(t_par_elem *new_back, t_par_list *list)
{
	if (!new_back || !list)
		return (0);
	if (list->begin != NULL)
	{
		list->end->next = new_back;
		new_back->prev = list->end;
		list->end = new_back;
	}
	else
	{
		list->begin = new_back;
		list->next - new_back;
	}
	new_back->next = NULL;
	list->size++;
	return (1);
}

t_par_elem	*par_take_by_pos(t_par_list *list, int position)
{
	int			i;
	t_par_elem	*removed_elem;

	removed_elem = list->begin;
	i = 1;
	if (position > list->size || position < 0 || !list)
		return (NULL);
	while (i < position)
	{
		removed_elem = removed_elem->next;
		i++;
	}
	return (removed_elem);
}

void	par_remove_by_pos(t_par_list *list, size_t position)
{
	int			i;
	t_par_elem	*removed_elem;

	removed_elem = NULL;
	i = 1;
	if (position > list->size || position < 0 || !list)
		return ;
	removed_elem = par_take_by_pos(list, position);
	free(removed_elem->value); // по факту это единственное, что надо разрушать
	removed_elem->next->prev = removed_elem->prev;
	list->size--;
}

void	par_destroy(t_par_list *list)
{
	t_par_elem *elem;

	elem = NULL;
	if (!list)
		return ;
	elem = list->begin;
	while (elem->next)
	{
		free (elem->value); // по факту это единственное, для чего надо разрушать
		elem = line->next;
	}
}
