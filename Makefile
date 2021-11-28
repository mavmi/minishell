sadfNAME		=	minishell


SRCS_DIR	=	srcs
FUNCS_DIR	=	$(SRCS_DIR)/rebuilt_funcs
ENV_DIR		=	$(SRCS_DIR)/enviroment
PROC_DIR	=	$(SRCS_DIR)/processes
UTILS_DIR	=	$(SRCS_DIR)/utils
PARS_DIR_	=	$(SRCS_DIR)/parser_
HDRS_DIR	=	include
READLN_DIR	=	readline


TESTS_DIR	=	tests
TESTS_PIPE	=	$(TESTS_DIR)/multi_pipe
TESTS_HE_DO	=	$(TESTS_DIR)/here_doc
TESTS_PARS	=	$(TESTS_DIR)/parser
TESTS_PARS_	=	$(TESTS_DIR)/parser_


HDRS		=	$(addprefix $(HDRS_DIR)/, rebuilt_funcs.h enviroment.h utils.h pipex.h variables.h parser_.h)
SRC_MAIN	= 	$(addprefix $(SRCS_DIR)/, minishell.c)
SRCS		= 	$(addprefix $(FUNCS_DIR)/, utils.c pwd.c cd.c env.c export.c unset.c echo.c exit.c)\
				$(addprefix $(ENV_DIR)/, env_1.c env_2.c env_3.c env_utils.c)\
				$(addprefix $(PROC_DIR)/, proc_files.c proc_paths.c proc_1.c proc_2.c proc_3.c proc_4.c proc_here_doc.c)\
				$(addprefix $(UTILS_DIR)/, utils_1.c)\
				$(addprefix $(PARS_DIR_)/, pars_list.c pars_split.c pars_utils.c pars_string_1.c pars_string_2.c pars_inter_1.c pars_inter_2.c)
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


CUR_TEST	=	0
GPP			=	g++ -std=c++17 -w $(OBJS) $(LIBFT) $(READLN) -I $(READLN_DIR) -ltermcap $(CUR_TEST)/test.cpp -o $(CUR_TEST)/test.out


all:			compile_libft $(NAME)

%.o:			%.c $(LIBFT) $(READLN) $(HDRS)
				$(GCC) -c -o $@ $<
 
$(NAME):		$(OBJS) $(OBJ_MAIN)
				$(GCC) $(OBJS) $(OBJ_MAIN) $(LIBFT) $(READLN) -I $(READLN_DIR) -I $(HDRS_DIR) -ltermcap -o $(NAME)

compile_libft:	
				$(MAKE) -C $(LIBFT_DIR)

clean:				
				rm -f $(OBJS) $(OBJ_MAIN)
				$(MAKE) clean -C $(LIBFT_DIR)

fclean:			clean
				rm -f $(NAME)
				$(MAKE) fclean -C $(LIBFT_DIR)

re:				fclean all

norm:			
				@echo "$(BLUE)\n\t*** HEADERS ***$(NC)"
				@norminette $(HDRS_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

				@echo "$(BLUE)\n\t*** MAIN ***$(NC)"
				@norminette $(SRC_MAIN) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

				@echo "$(BLUE)\n\t*** FUNCS ***$(NC)"
				@norminette $(FUNCS_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

				@echo "$(BLUE)\n\t*** ENV ***$(NC)"
				@norminette $(ENV_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

				@echo "$(BLUE)\n\t*** PIPEX ***$(NC)"
				@norminette $(PROC_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

				@echo "$(BLUE)\n\t*** UTILS ***$(NC)"
				@norminette $(UTILS_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

#				@echo "$(BLUE)\n\t*** PARSER ***$(NC)"
#				@norminette $(PARS_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'
				
				@echo "$(BLUE)\n\t*** MY PARSER ***$(NC)"
				@norminette $(PARS_DIR_) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

tests:			compile_libft $(OBJS)
				$(eval CUR_TEST := $(TESTS_PIPE))
				$(GPP)

				$(eval CUR_TEST := $(TESTS_HE_DO))
				$(GPP)

				$(eval CUR_TEST := $(TESTS_PARS))
				$(GPP)

				$(eval CUR_TEST := $(TESTS_PARS_))
				$(GPP)

.PHONY:			all compile_libft clean fclean re tests norm
