/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 12:41:37 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/14 13:03:37 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

# include <stdlib.h>

# include "utils.h"
# include "../libft/libft.h"

typedef struct s_var	t_var;

struct s_var
{
	char	*name;
	char	*value;
	t_var	*next;
};

t_var	*var_get_new_elem(char *name, char *value);
void	var_destroy_elem(t_var *elem);
void	var_push_back(t_var *list, t_var *elem);
void	var_destroy_list(t_var *list);

t_var	*var_get(t_var *list, char *name);
void	var_remove(t_var **list, char *name);

#endif
