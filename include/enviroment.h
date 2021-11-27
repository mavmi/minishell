/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:52:03 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/27 15:48:18 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_H
# define ENVIROMENT_H

# include <stdio.h>

# include "../libft/libft.h"
# include "utils.h"

typedef struct s_env_elem	t_env_elem;
typedef struct s_enviroment	t_enviroment;
typedef struct s_data		t_data;

struct s_env_elem
{
	char		*name;
	char		*value;
	t_env_elem	*next;
	t_env_elem	*prev;
};

struct s_enviroment
{
	size_t		size;
	t_env_elem	*begin;
	t_env_elem	*end;
};

struct s_data
{
	int				exit_status;
	t_enviroment	*envp;
};

t_data						g_data;

// env_1.c
t_env_elem		*env_get_new_elem(char *str);
int				env_push_back(t_enviroment *env, char *str);
char			**env_get_content(t_enviroment *env);

// env_2.c
void			env_remove_elem(t_enviroment *env, char *name);
void			env_destroy(t_enviroment *env);
t_enviroment	*env_create_empty(void);
t_enviroment	*env_create(char **envp);

// env_3.c
t_env_elem		*env_get_by_position(t_enviroment *env, size_t pos);
t_env_elem		*env_get_by_name(t_enviroment *env, char *name);
int				env_set_by_position(t_enviroment *env,
					size_t pos, char *new_val);
int				env_set_by_name(t_enviroment *env, char *name, char *new_val);

#endif
