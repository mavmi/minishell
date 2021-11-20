/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:08:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/20 13:25:39 by pmaryjo          ###   ########.fr       */
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
typedef struct s_strings	t_strings;

struct s_pars_list
{
	int			type;
	char		*value;
	t_pars_list	*next;
};

struct s_strings
{
	char		*string;
	t_strings	*next;	
};

t_pars_list	*pars_get_new_elem(int type, char *value);
void		pars_push_back(t_pars_list *list, t_pars_list *elem);
void		pars_destroy_elem(t_pars_list *elem);
void		pars_destroy_list(t_pars_list *list);

t_pars_list	*pars_split(char *cmd);

char		**pars_get_operators(void);
int			pars_cmp_with_opers(char *cmd, char **opers);
int			pars_insert_elem(t_pars_list **list, char *str, int type);
int			pars_get_substr_len(char *cmd, char **opers);
int			pars_is_forbidden(char *cmd);

t_strings	*pars_get_new_str_elem(char *str);
void		pars_destroy_str_elem(t_strings *elem);
void		pars_destroy_str_list(t_strings *list);
void		pars_push_back_str(t_strings *list, t_strings *elem);

char		*pars_get_whole_string(t_strings *list);

#endif
