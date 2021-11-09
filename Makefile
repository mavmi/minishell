NAME		=	minishell


SRCS_DIR	=	srcs
FUNCS_DIR	=	$(SRCS_DIR)/rebuilt_funcs
ENV_DIR		=	$(SRCS_DIR)/enviroment
PIPEX_DIR	=	$(SRCS_DIR)/pipex
GNL_DIR		=	$(SRCS_DIR)/get_next_line
UTILS_DIR	=	$(SRCS_DIR)/utils
HDRS_DIR	=	include
READLN_DIR	=	readline


TESTS_DIR	=	tests
TESTS_PIPE	=	$(TESTS_DIR)/multi_pipe


HDRS		=	$(addprefix $(HDRS_DIR)/, minishell.h rebuilt_funcs.h enviroment.h utils.h pipex.h get_next_line)
SRC_MAIN	= 	$(addprefix $(SRCS_DIR)/, minishell.c)
SRCS		= 	$(addprefix $(SRCS_DIR)/, signals.c)\
				$(addprefix $(FUNCS_DIR)/, utils.c pwd.c cd.c env.c export.c unset.c echo.c exit.c)\
				$(addprefix $(ENV_DIR)/, env_1.c env_2.c env_3.c)\
				$(addprefix $(PIPEX_DIR)/, files_checker.c paths.c pipex_1.c pipex_2.c pipex_3.c here_doc.c)\
				$(addprefix $(UTILS_DIR)/, utils_1.c utils_2.c)
#				$(addprefix $(GNL_DIR)/, get_next_line.c get_next_line_utils.c)
OBJ_MAIN	=	$(SRC_MAIN:.c=.o)
OBJS		=	$(SRCS:.c=.o)


LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a


READLN_HDRS	=	$(addprefix $(READLN_DIR)/, chardefs.h history.h keymaps.h readline.h rlconf.h rlstdc.h rltypedefs.h tilde.h)
READLN		=	$(addprefix $(READLN_DIR)/, libhistory.a libreadline.a)


BLUE		=	\033[34m
CYAN		=	\033[36m
NC			=	\033[0m


FLAGS		=	-Wall -Wextra -Werror -g
CC			=	gcc
GCC			=	$(CC) $(FLAGS)


all:			compile_libft $(NAME)

%.o:			%.c $(LIBFT) $(READLN) $(HDRS)
				$(GCC) -c -o $@ $<
 
$(NAME):		$(OBJS) $(OBJ_MAIN)
				$(GCC) $(OBJS) $(OBJ_MAIN) $(LIBFT) $(READLN) -I $(READLN_DIR) -I $(HDRS_DIR) -ltermcap -o $(NAME)

compile_libft:	
				$(MAKE) -C $(LIBFT_DIR)

clean:				
				rm -f $(OBJS)
				$(MAKE) clean -C $(LIBFT_DIR)

fclean:			clean
				rm -f $(NAME)
				$(MAKE) fclean -C $(LIBFT_DIR)

re:				fclean all

norm:			
				@echo "$(BLUE)\n\t*** HEADERS ***$(NC)"
				@norminette $(HDRS_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

				@echo "$(BLUE)\n\t*** FUNCS ***$(NC)"
				@norminette $(FUNCS_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

				@echo "$(BLUE)\n\t*** ENV ***$(NC)"
				@norminette $(ENV_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

				@echo "$(BLUE)\n\t*** PIPEX ***$(NC)"
				@norminette $(PIPEX_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

				@echo "$(BLUE)\n\t*** UTILS ***$(NC)"
				@norminette $(UTILS_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

				@echo "$(BLUE)\n\t*** GNL ***$(NC)"
				@norminette $(GNL_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

tests:			compile_libft $(OBJS)
				g++ -std=c++17 -Wall -Wextra -Werror $(OBJS) $(LIBFT) $(READLN) -I $(READLN_DIR) -ltermcap $(TESTS_PIPE)/test.cpp -o $(TESTS_PIPE)/test.out

.PHONY:			all compile_libft clean fclean re tests norm
