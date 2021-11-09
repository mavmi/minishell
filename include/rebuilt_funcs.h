/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuilt_funcs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:31:39 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/09 18:37:45 by pmaryjo          ###   ########.fr       */
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
# include "utils.h"

# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

int		is_rebuild(char *func);
void	my_pwd(void);
void	my_cd(int argc, char **argv);
void	my_env(void);
void	my_export(int argc, char **argv);
void	my_unset(int argc, char **argv);
void	my_echo(int argc, char **argv);
void	my_exit(void);

#endif
