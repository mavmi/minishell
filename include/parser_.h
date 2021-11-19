/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:08:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/19 19:23:43 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER__H
# define PARSER__H

# define DEFAULT_N -1

# define REDIR_OUT_N 0
# define REDIR_INP_N 1
# define REDIR_OUT_APP_N 2
# define HERE_DOC_N 3
# define PIPE_N 4
# define DOLL_N 5
# define EQUAL_N 6

# define REDIR_OUT_S ">"
# define REDIR_INP_S "<"
# define REDIR_OUT_APP_S ">>"
# define HERE_DOR_S "<<"
# define PIPE_S "|"
# define DOLL_S "$"
# define EQUAL_S "="

# define OPERATORS 7

# include "../libft/libft.h"
# include "utils.h"

typedef struct s_pars_list	t_pars_list;

struct s_pars_list
{
	int			type;
	char		*value;
	t_pars_list	*next;
};

char		**pars_get_operators(void);
t_pars_list	*pars_get_new_elem(int type, char *value);
void		pars_push_back(t_pars_list *list, t_pars_list *elem);
void		pars_destroy_elem(t_pars_list *elem);
void		pars_destroy_list(t_pars_list *list);

t_pars_list	*pars_split(char *cmd);

int			pars_cmp_with_opers(char *cmd, char **opers);
int			pars_insert_elem(t_pars_list **list, char *str, int type);
int			pars_get_substr_len(char *cmd, char **opers);

#endif