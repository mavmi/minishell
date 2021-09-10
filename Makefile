NAME		=	minishell


SRCS_DIR	=	srcs
FUNCS_DIR	=	$(SRCS_DIR)/rebuilt_funcs
ENV_DIR		=	$(SRCS_DIR)/enviroment
PIPEX_DIR	=	$(SRCS_DIR)/pipex
GNL_DIR		=	$(SRCS_DIR)/get_next_line
HDRS_DIR	=	include
READLN_DIR	=	readline

HDRS		=	$(addprefix $(HDRS_DIR)/, minishell.h rebuilt_funcs.h enviroment.h utils.h pipex.h get_next_line)
SRCS		= 	$(addprefix $(SRCS_DIR)/, minishell.c signals.c utils.c)\
				$(addprefix $(FUNCS_DIR)/, pwd.c cd.c env.c export.c unset.c)\
				$(addprefix $(ENV_DIR)/, env_1.c env_2.c env_3.c)\
				$(addprefix $(PIPEX_DIR)/, files_checker.c paths.c pipex_1.c pipex_2.c)\
				$(addprefix $(GNL_DIR)/, get_next_line.c get_next_line_utils.c)
OBJS		=	$(SRCS:.c=.o)


LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a


READLN_HDRS	=	$(addprefix $(READLN_DIR)/, chardefs.h history.h keymaps.h readline.h rlconf.h rlstdc.h rltypedefs.h tilde.h)
READLN		=	$(addprefix $(READLN_DIR)/, libhistory.a libreadline.a)


#READLN_DIR	=	readline
#READLN		=	$(addprefix $(READLN_DIR)/, libhistory.a libreadline.a)


FLAGS		=	-Wall -Wextra -Werror -g
CC			=	gcc
GCC			=	$(CC) $(FLAGS)


all:			compile_libft $(NAME)

%.o:			%.c $(LIBFT) $(READLN) $(HDRS)
				$(GCC) -c -o $@ $<
 
$(NAME):		$(OBJS)
				$(GCC) $(OBJS) $(LIBFT) $(READLN) -I $(READLN_DIR) -I $(HDRS_DIR) -ltermcap -o $(NAME)
#				$(GCC) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
#				$(GCC) $(OBJS) $(LIBFT) $(READLN) -o $(NAME)

compile_libft:	
				$(MAKE) -C $(LIBFT_DIR)

clean:				
				rm -f $(OBJS)
				$(MAKE) clean -C $(LIBFT_DIR)

fclean:			clean
				rm -f $(NAME)
				$(MAKE) fclean -C $(LIBFT_DIR)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
