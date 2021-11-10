/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuilt_funcs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:31:39 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/10 14:36:09 by pmaryjo          ###   ########.fr       */
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

int		rebuit_is_rebuilt(char *func);
void	rebuilt_call_func(int argc, char **argv);

void	rebuilt_pwd(void);
void	rebuilt_cd(int argc, char **argv);
void	rebuilt_env(void);
void	rebuilt_export(int argc, char **argv);
void	rebuilt_unset(int argc, char **argv);
void	rebuilt_echo(int argc, char **argv);
void	rebuilt_exit(void);

#endif
