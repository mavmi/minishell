/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuilt_funcs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:31:39 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/04 19:21:52 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REBUILT_FUNCS_H
# define REBUILT_FUNCS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>

# include "minishell.h"

void	set_env(char *name, char *new_value);
void	pwd(void);
void	env(void);
void	cd(int argc, char **argv);

#endif
