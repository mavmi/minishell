/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:57:00 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/27 15:57:00 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define PROMT "minishel> "

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

# include "../libft/libft.h"

# include "../readline/chardefs.h"
# include "../readline/history.h"
# include "../readline/keymaps.h"
# include "../readline/readline.h"
# include "../readline/rlconf.h"
# include "../readline/rlstdc.h"
# include "../readline/rltypedefs.h"
# include "../readline/tilde.h"

// utils_1.c
char	*utils_create_lone_string(char *name, char *value);
int		utils_cmp_strings(char *s1, char *s2);
char	*utils_sum_strings(char *s1, char *s2);
void	utils_append_string(char **str, char *value);
void	utils_destroy_strings_array(char **arr);

#endif
