/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:30:03 by msalena           #+#    #+#             */
/*   Updated: 2021/10/27 23:11:16 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

/* Frees operations arr and/or list */
t_par_list	*par_free_out(char **oper_arr, t_par_list *list)
{
	if (!oper_arr && !list)
		return (NULL);
	else if (!oper_arr)
		par_destroy_all(list);
	else if (!list)
		free(oper_arr);
	else
	{
		free(oper_arr);
		par_destroy_all(list);
	}
	return (NULL);
}

char	*par_check_malloc(char *str)
{
	char	*return_str;

	if (!str)
		return (NULL);
	return_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!return_str)
	{
		free (str);
		return (NULL);
	}
	return (return_str);
}

/* compares input elem of cmd with define operators
--> return number of rediretive if match
	or -1 (DEFAULT) if cmd[i] doesn't match */
int	par_compar_cNo(char *cmd, t_par_count *coun, char **oper)
{
	int	n_str;
	int	t;
	int	n_el;

	t = 0;
	n_str = 0;
	n_el = 0;
	coun->size = 0;
	coun->num = DEFAULT_N;
	if (!cmd || !coun || !oper)
		return (0);
	while (oper[n_str])
	{
		while (oper[n_str][n_el] && cmd[t] && cmd[t++] == oper[n_str][n_el])
			n_el++;
		if (!oper[n_str][n_el] && n_el > coun->size)
		{
			coun->size = n_el;
			coun->num = n_str;
		}
		n_el = 0;
		t = 0;
		n_str++;
	}
	return (coun->num);
}

/* Finds quotion marks */
static char	*between_quotes(char *str, char *return_str,
							int *str_c, int *retstr_c)
{
	char	quote;

	quote = 0;
	quote = str[*str_c];
	return_str[(*retstr_c)++] = str[(*str_c)++];
	while (str[*str_c] != quote)
	{
		return_str[(*retstr_c)++] = str[(*str_c)++];
	}
	return_str[(*retstr_c)++] = str[(*str_c)++];
	return (return_str);
}

/* Handls quotes in substr
--> return changed substr
	or NULL if some mistake */
char	*par_handling_quotes(char *str)
{
	int		str_c;
	int		retstr_c;
	char	*return_str;

	str_c = 0;
	retstr_c = 0;
	if (!str)
		return (NULL);
	return_str = par_check_malloc(str);
	if (!return_str)
		return (NULL);
	while (str[str_c])
	{
		while (str[str_c] && str[str_c] != '\'' && str[str_c] != '\"')
			return_str[retstr_c++] = str[str_c++];
		if (str[str_c] == '\'' || str[str_c] == '\"')
			between_quotes(str, return_str, &str_c, &retstr_c);
	}
	return_str[retstr_c] = '\0';
	free (str);
	return (return_str);
}


int	main(void)
{
	//FOR_PAR// gcc -Wall -Wextra -Werror srcs/parser/parser_1.c srcs/parser/parser_initial.c srcs/parser/parser_operations.c srcs/parser/parser_0.c libft/ft_strlen.c libft/ft_strdup.c  && leaks --atExit -- ./a.out

	//FOR_ARR// gcc -Wall -Wextra -Werror srcs/parser/parser_cmd_array.c srcs/parser/parser_1.c srcs/parser/parser_initial.c srcs/parser/parser_operations.c srcs/parser/parser_0.c libft/libft.a srcs/utils/utils_2.c && ./a.out | cat -e

// valgrind --log-file=valgrind_output.txt --tool=memcheck --leak-check=yes

/* MAIN FOR HANDLING QUOTES TESTING*/

// 	// char	str[6] = "\"text\""; // "text"
// 	// char	str[6] = "\'text\'"; // 'text'
// 	// char	str[8] = "\"te\'xt\""; // "te'xt"
// 	// char	str[8] = "\'te\"xt\'"; // 'te"xt'

// 	// char	str[13] = "\"text\"\"text\""; // "text""text"
	// char	str[13] = "\'text\'\'text\'"; // 'text''text'
// 	// char	str[13] = "\"text\"\'text\'"; // "text"'text'
	// char	str[13] = "\'text\'\"text\""; // 'text'"text"

	// char	str[13] = "\'text\'text\"\""; // 'text'text""

// 	//~~~~~~~~~~~~~~~~~~~~~~~~~~mistakes~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 	// char	str[13] = "\"text\\\"text\""; //"text\"text"
// 	// char	str[13] = "\'text\\\'text\'"; //'text\'text'
// 	// char	str[13] = "\'text\\\"text\'"; //'text\"text'
// 	// char	str[13] = "\"text\\\"text\""; //"text\'text"

	// char	str[12] = "\'text\'text\'"; //'text'text'
// 	// char	str[12] = "\"text\"text\""; //"text"text"
// 	// char	str[12] = "\"text\'text\'"; //"text'text'
	// char	str[12] = "\'text\"text\""; //'text"text"

// 	// char	str[13] = "\'text\'\"text\'"; //'text'"text'
	// char	str[13] = "\"text\"\'text\""; //'text'"text'

	// char	str[52] = "cat $         ABS=123 \"doll $doll\"";
	// printf("ret_str = %s \n", handling_quotes(str));
	// char	str[100] = "<input_file cat|grep    \'$vFJFJFJ\'  SUBSTRING >output_file ";
	char	str[65] = "<<cat -e jjjj| \"<\"<STOP file.c cat -e >file.c file.c";//cat";
	t_par_list	*list;
	t_par_elem	*elem;

	list = par_split(str);
	if (!list)
	{
		printf ("NULL\n");
		return (0);
	}
	elem = list->begin;

	/////////for_par_split_outputing////////////
	while (elem->next)
	{
		printf ("type_str= %d  ---------          ", elem->type);
		printf("str_of_arr =%s                 num = %d\n", elem->value, elem->number_pos);
		elem = elem->next;
	}
	printf ("type_str= %d  ---------          ", elem->type);
	printf("str_of_arr =%s\n", elem->value);

	///////////////////////////////////////////


	///////////////////////////////////////////////
	// open("lsadfj", O_RDONLY);
	// printf("minishell: %s: %s\n", "filename", strerror(errno));
	// return 1;
	/////////////////////////////////////////////////


	// char	**arr = arr_cmd_formation(list);
	// int		i = 0;

	// while (arr && arr[i])
	// {
	// 	printf ("arr[%d]: %s\n", i, arr[i]);
	// 	i++;
	// }
	// for (int i=0; arr && arr[i]; i++)
	// 	free (arr[i]);
	// free (arr);


	par_destroy_all(list);
// sleep (1000);
	return (0);
}
