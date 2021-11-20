/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:57:00 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/20 13:33:10 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

# include "minishell.h"

char	*utils_create_lone_string(char *name, char *value);
char	**utils_parse_varialbe(char *str);

int		utils_is_string_valid(char *str);
int		utils_cmp_strings(char *s1, char *s2);
void	utils_destroy_strings_array(char **arr);
char	*utils_sum_strings(char *s1, char *s2);
void 	utils_append_string(char **str, char *value);

#endif
