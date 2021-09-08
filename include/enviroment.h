/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 17:34:35 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/08 16:11:46 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_H
# define ENVIROMENT_H

# include "minishell.h"

typedef struct s_env_elem	t_env_elem;
typedef struct s_enviroment	t_enviroment;

struct s_env_elem
{
	char		*name;
	char		*value;
	t_env_elem	*next;
};

struct s_enviroment
{
	size_t		size;
	t_env_elem	*begin;
	t_env_elem	*end;
};

t_env_elem		*env_get_new_elem(char *str);
int				env_push_back(t_enviroment *env, char *str);
t_env_elem		*env_get_by_position(t_enviroment *env, size_t pos);
t_env_elem		*env_get_by_name(t_enviroment *env, char *name);
int				env_set_by_position(t_enviroment *env,
					size_t pos, char *new_val);
int				env_set_by_name(t_enviroment *env, char *name, char *new_val);
char			**env_get_content(t_enviroment *env);
void			env_destroy(t_enviroment *env);
t_enviroment	*env_create_empty(void);
t_enviroment	*env_create(char **envp);

#endif
