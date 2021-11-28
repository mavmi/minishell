/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:50:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/03 15:50:12 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*next;

	if (!*lst)
		return ;
	next = *lst;
	while (next)
	{
		ptr = next;
		(*del)(ptr->content);
		next = ptr->next;
		free(ptr);
	}
	*lst = NULL;
}
