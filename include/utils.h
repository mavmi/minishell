/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:57:00 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/10 20:23:47 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

# include "minishell.h"

char	*create_lone_string(char *name, char *value);
int		is_string_valid(char *str);
int		cmp_strings(char *s1, char *s2);
void	destroy_strings_array(char **arr);
char	**parse_varialbe(char *str);

#endif
