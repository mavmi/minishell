/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuilt_funcs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:31:39 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/11 13:13:37 by pmaryjo          ###   ########.fr       */
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

void	my_pwd(void);
void	my_cd(int argc, char **argv);
void	my_env(void);
void	my_export(int argc, char **argv);
void	my_unset(int argc, char **argv);
void	my_echo(int argc, char **argv);
void	my_exit(void);

#endif
