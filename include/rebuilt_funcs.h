/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuilt_funcs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:31:39 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/19 17:42:56 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REBUILT_FUNCS_H
# define REBUILT_FUNCS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>

# include "enviroment.h"
# include "utils.h"

# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

// utils.c
int		rebuit_is_rebuilt(char *func);
void	rebuilt_call_func(int argc, char **argv, int fd_out);
int		rebuilt_is_valid_name(char *name);

void	rebuilt_export(int argc, char **argv, int fd_out);
void	add_empty(char *new_name);
void	add_value(char *new_name, char *new_val);

void	rebuilt_pwd(int fd_out);
void	rebuilt_cd(int argc, char **argv);
void	rebuilt_env(int fd_out);
void	rebuilt_unset(int argc, char **argv);
void	rebuilt_echo(int argc, char **argv, int fd_out);
void	rebuilt_exit(int argc, char **argv);

#endif
