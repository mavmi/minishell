/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:08:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/27 14:40:20 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER__H
# define PARSER__H

# define DEFAULT -1
# define DOLL_S "$"
# define QUES_S "?"

# define REDIR_OUT 0
# define REDIR_INP 1
# define REDIR_OUT_APP 2
# define HERE_DOC_ 3
# define PIPE 4

# define REDIR_OUT_S ">"
# define REDIR_INP_S "<"
# define REDIR_OUT_APP_S ">>"
# define HERE_DOR_S "<<"
# define PIPE_S "|"

# define OPERATORS 5

# include "../libft/libft.h"
# include "utils.h"
# include "pipex.h"

typedef struct s_pars_list	t_pars_list;
typedef struct s_strings	t_strings;

struct s_pars_list
{
	int			type;
	char		*value;
	t_pars_list	*next;
};

t_pars_list			*pars_get_new_elem(int type, char *value);
void				pars_push_back(t_pars_list *list, t_pars_list *elem);
void				pars_destroy_elem(t_pars_list *elem);
void				pars_destroy_list(t_pars_list *list);

t_pars_list			*pars_split(char *cmd);

char				**pars_get_operators(void);
int					pars_cmp_with_opers(char *cmd, char **opers);
int					pars_insert_elem(t_pars_list **list, char *str, int type);
int					pars_get_substr_len(char *cmd, char **opers);
int					pars_is_forbidden(char *cmd);

char				*pars_get_whole_string(char *input);

char				*pars_handle_substr(char *str);

struct s_process	*pars_intepret(t_pars_list *pars_list);

#endif
