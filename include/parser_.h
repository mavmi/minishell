/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:08:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/28 16:46:23 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER__H
# define PARSER__H

# define DEFAULT -1
# define DOLL_S "$"
# define QUES_S "?"

# define REDIR_OUT_ 0
# define REDIR_INP_ 1
# define REDIR_OUT_APP_ 2
# define HERE_DOC_ 3
# define PIPE_ 4

# define REDIR_OUT_S_ ">"
# define REDIR_INP_S_ "<"
# define REDIR_OUT_APP_S_ ">>"
# define HERE_DOR_S_ "<<"
# define PIPE_S_ "|"

# define OPERATORS 5

# include "../libft/libft.h"
# include "utils.h"
# include "processes.h"

typedef struct s_pars_list	t_pars_list;
typedef struct s_strings	t_strings;

struct s_pars_list
{
	int			type;
	char		*value;
	t_pars_list	*next;
};

// pars_list.c
t_pars_list	*pars_get_new_elem(int type, char *value);
void		pars_push_back(t_pars_list *list, t_pars_list *elem);
void		pars_destroy_elem(t_pars_list *elem);
void		pars_destroy_list(t_pars_list *list);

// pars_split.c
t_pars_list	*pars_split(char *cmd);

// pars_utils.c
char		**pars_get_operators(void);
int			pars_cmp_with_opers(char *cmd, char **opers);
int			pars_insert_elem(t_pars_list **list, char *str, int type);
int			pars_get_substr_len(char *cmd, char **opers);
int			pars_is_forbidden(char *cmd);

// pars_string_1.c
char		*pars_handle_substring(char *input);

// pars_string_2.c
char		*pars_handle_substr(char *str);

// pars_inter_1.c
t_process	*pars_intepret(t_pars_list *pars_list);

// pars_inter_2.c
int			pars_check_list_validity(t_pars_list *pars_list);

#endif
