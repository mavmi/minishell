#ifndef PARSER_H
# define PARSER_H

#define DEFAULT_N -1
#define REDIR_INP_N 0

# define REDIR_INP1_S ">"
# define REDIR_INP2_S "<"
# define REDIR_INP2_S "<"
# define REDIR_INP3_S ">>"
# define REDIR_INP4_S "<<"
# define REDIR_INP5_S "|"

# include "../libft/libft.h"
# include "utils.h"

typedef struct s_par_elem    t_par_elem;
typedef struct s_par_list    t_par_list;

struct s_par_elem
{
	int			type;
	char		*value;
	t_par_elem	*next;
	t_par_elem	*prev;
};

struct t_parser_list
{
	size_t		size;
	t_par_elem	*begin;
	t_par_elem	*end;
};


t_par_list	*par_initial_empty_list(void);
t_par_elem	*par_get_new_elem(int type, char *value, t_par_list *list);

char		**par_get_redirect(void);

int			par_push_back(t_par_elem *new_back, t_par_list *list);
t_par_elem	par_take_by_pos(t_par_list *list, int position);
int			par_remove_by_pos(t_par_list *list, size_t position);


#endif
