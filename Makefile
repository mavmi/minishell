# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 19:05:38 by msalena           #+#    #+#              #
#    Updated: 2021/12/19 17:42:04 by pmaryjo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell


SRCS_DIR	=	srcs
FUNCS_DIR	=	$(SRCS_DIR)/rebuilt_funcs
ENV_DIR		=	$(SRCS_DIR)/enviroment
PROC_DIR	=	$(SRCS_DIR)/processes
UTILS_DIR	=	$(SRCS_DIR)/utils
PARS_DIR	=	$(SRCS_DIR)/parser
HDRS_DIR	=	include
READLN_DIR	=	readline


HDRS		=	$(addprefix $(HDRS_DIR)/, rebuilt_funcs.h enviroment.h utils.h pipex.h variables.h signal.h)
SRCS		= 	$(addprefix $(SRCS_DIR)/, minishell.c)\
			 	$(addprefix $(FUNCS_DIR)/, utils.c pwd.c cd.c env.c export_1.c export_2.c unset.c echo.c exit.c)\
				$(addprefix $(ENV_DIR)/, env_1.c env_2.c env_3.c env_4.c env_utils.c env_sort.c)\
				$(addprefix $(PROC_DIR)/, proc_files.c proc_paths.c proc_1.c proc_2.c proc_3.c proc_4.c proc_here_doc.c proc_split.c)\
				$(addprefix $(UTILS_DIR)/, utils_1.c)\
				$(addprefix $(PARS_DIR)/, parser_0.c parser_1.c parser_cmd_array.c parser_fd_array.c\
											parser_initial.c parser_operations.c parser_handle_quotes_1.c\
											parser_handle_quotes_2.c parser_handle_quotes_3.c parser_list_checker.c\
											parser_signal.c parser_steps_execution.c parser_utils.c)
OBJS		=	$(SRCS:.c=.o)
DEPEN		=	$(OBJS:.o=.d)


LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a


READLN_HDRS	=	$(addprefix $(READLN_DIR)/, chardefs.h history.h keymaps.h readline.h rlconf.h rlstdc.h rltypedefs.h tilde.h)
READLN		=	$(addprefix $(READLN_DIR)/, libhistory.a libreadline.a)


# Norminette colors
BLUE		=	\033[34m
CYAN		=	\033[36m
NC			=	\033[0m


FLAGS		=	-Wall -Wextra -Werror -MMD -g
CC			=	gcc
GCC			=	$(CC) $(FLAGS)


all:			compile_libft $(NAME)

%.o:			%.c
				$(GCC) -I $(READLN_DIR) -I $(HDRS_DIR) -c -o $@ $<

$(NAME):		$(OBJS) Makefile
				$(GCC) $(OBJS) $(LIBFT) $(READLN) -ltermcap -o $(NAME)

compile_libft:
				$(MAKE) -C $(LIBFT_DIR)

clean:
				rm -f $(OBJS) $(DEPEN)
				$(MAKE) clean -C $(LIBFT_DIR)

fclean:			clean
				rm -f $(NAME)
				$(MAKE) fclean -C $(LIBFT_DIR)

re:				fclean all

norm:
				@echo "$(BLUE)\n\t*** HEADERS ***$(NC)"
				@norminette $(HDRS_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

				@echo "$(BLUE)\n\t*** SRCS_DIR ***$(NC)"
				@norminette $(SRCS_DIR)/*.c | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

				@echo "$(BLUE)\n\t*** FUNCS ***$(NC)"
				@norminette $(FUNCS_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

				@echo "$(BLUE)\n\t*** ENV ***$(NC)"
				@norminette $(ENV_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

				@echo "$(BLUE)\n\t*** PROCESSES ***$(NC)"
				@norminette $(PROC_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

				@echo "$(BLUE)\n\t*** UTILS ***$(NC)"
				@norminette $(UTILS_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

				@echo "$(BLUE)\n\t*** PARSER ***$(NC)"
				@norminette $(PARS_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

				@echo "$(BLUE)\n\t*** LIBFT ***$(NC)"
				@norminette $(LIBFT_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

-include $(DEPEN)

.PHONY:			all compile_libft clean fclean re norm
