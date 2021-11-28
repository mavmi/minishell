/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:29:51 by msalena           #+#    #+#             */
/*   Updated: 2021/10/26 19:29:52 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define DEFAULT_N -1
# define OPER_OUT_N 0
# define OPER_INP_N 1
# define OPER_OUT_APP_N 2
# define OPER_HERE_DOC_N 3
# define OPER_PIPE_N 4
# define OPER_DOLL_N 5

# define OPER_OUT_S ">"
# define OPER_INP_S "<"
# define OPER_OUT_APP_S ">>"
# define OPER_HERE_DOC_S "<<"
# define OPER_PIPE_S "|"
# define OPER_DOLL_S "$"

// # include "minishell.h"
# include "../libft/libft.h"
# include <stdio.h>
# include "utils.h"
# include "processes.h"

typedef struct s_par_elem	t_par_elem;
typedef struct s_par_list	t_par_list;
typedef struct s_par_count	t_par_count;

struct s_par_elem
{
	int			type;
	char		*value;
	size_t		number_pos;
	t_par_elem	*next;
	t_par_elem	*prev;
};

struct s_par_list
{
	size_t		size;
	t_par_elem	*begin;
	t_par_elem	*end;
};

struct s_par_count
{
	int		size;
	int		num;
	int		i_elem;
};

t_par_list	*par_initial_empty_list(void);
t_par_elem	*par_get_new_elem(int type, char *value, size_t num);
char		**par_get_redirect(void);
t_par_elem	*par_get_by_pos(t_par_list *list, size_t position);
t_par_count	count_initial(void);

int			par_push_back(t_par_elem *new_back, t_par_list *list);
void		par_remove_by_pos(t_par_list *list, size_t position);
void		par_destroy_elem(t_par_elem *elem);
void		par_destroy_all(t_par_list *list);

t_par_list	*par_split(char *cmd);

t_par_list	*par_free_out(char **oper_arr, t_par_list *list);
char		*par_check_malloc(char *str);
int			par_compar_cNo(char *cmd, t_par_count *coun, char **arr);
char		*par_handling_quotes(char *str);

char		**arr_cmd_formation(t_par_list *elem_list);

#endif
