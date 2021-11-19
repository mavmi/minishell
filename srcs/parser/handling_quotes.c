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

/*	return number if rediretive or
	return -1 if cmd[i] doesn't match */
int	par_compar_cNo(char *cmd, t_par_count *coun, char **arr)
{
	int	n_str;
	int	tmp;
	int	n_el;

	tmp = 0;
	n_str = 0;
	n_el = 0;
	coun->size = 0;
	coun->num = DEFAULT_N;
	if (!cmd || !coun || !arr)
		return (0);
	while (arr[n_str])
	{
		while (arr[n_str][n_el] && cmd[tmp] && cmd[tmp++] == arr[n_str][n_el])
			n_el++;
		if (!arr[n_str][n_el] && n_el > coun->size)
		{
			coun->size = n_el;
			coun->num = n_str;
		}
		n_el = 0;
		tmp = 0;
		n_str++;
	}
	return (coun->num);
}

static void	between_quotes(char *str, char *return_str,
							int *str_c, int *retstr_c)
{
	char	quote;

	quote = 0;
	quote = str[*str_c];
	return_str[(*retstr_c)++] = str[(*str_c)++];
	while (str[*str_c] != quote)
		return_str[(*retstr_c)++] = str[(*str_c)++];
	return_str[(*retstr_c)++] = str[(*str_c)++];
}

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
		if (!par_check_on_slash(str, &str_c, return_str))
			return (NULL);
		while (str[str_c] && str[str_c] != '\'' && str[str_c] != '\"')
			return_str[retstr_c++] = str[str_c++];
		if (str[str_c] == '\'' || str[str_c] == '\"')
			between_quotes(str, return_str, &str_c, &retstr_c);
	}
	return_str[retstr_c] = '\0';
	return (return_str);
}


// int	main(void)
// {
// 	// gcc -Wall -Wextra -Werror srcs/parser/handling_quotes.c srcs/parser/parser_initial.c srcs/parser/parser_work_with_mallocs.c srcs/parser/parser_operations.c srcs/parser/parser.c libft/ft_strlen.c libft/ft_strdup.c
// 	/* MAIN FOR HANDLING QUOTES TESTING*/

// 	// char	str[6] = "\"text\""; // "text"
// 	// char	str[6] = "\'text\'"; // 'text'
// 	// char	str[8] = "\"te\'xt\""; // "te'xt"
// 	// char	str[8] = "\'te\"xt\'"; // 'te"xt'

// 	// char	str[13] = "\"text\"\"text\""; // "text""text"
// 	// char	str[13] = "\'text\'\'text\'"; // 'text''text'
// 	// char	str[13] = "\"text\"\'text\'"; // "text"'text'
// 	// char	str[13] = "\'text\'\"text\""; // 'text'"text"

// 	// char	str[13] = "\'text\'text\"\""; // 'text'text""

// 	//~~~~~~~~~~~~~~~~~~~~~~~~~~mistakes~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 	// char	str[13] = "\"text\\\"text\""; //"text\"text"
// 	// char	str[13] = "\'text\\\'text\'"; //'text\'text'
// 	// char	str[13] = "\'text\\\"text\'"; //'text\"text'
// 	// char	str[13] = "\"text\\\"text\""; //"text\'text"

// 	// char	str[12] = "\'text\'text\'"; //'text'text'
// 	// char	str[12] = "\"text\"text\""; //"text"text"
// 	// char	str[12] = "\"text\'text\'"; //"text'text'
// 	// char	str[12] = "\'text\"text\""; //'text"text"

// 	// char	str[13] = "\'text\'\"text\'"; //'text'"text'
// 	// char	str[13] = "\"text\"\'text\""; //'text'"text'

// 	// char	str[35] = "\"cat\"\'<<\'\"\""; //"cat<<" --- "cat" "<<" ""
// // // 	// printf("ret_str = %s \n", handling_quotes(str));
// 	char	str[100] = "<input_file cat|grep    \'$vFJFJFJ\'  SUBSTRING >output_file ";
// 	// char	str[5] = "$ cat";//cat";
// 	t_par_list	*list;
// 	t_par_elem	*elem;

// 	list = par_split(str);
// 	if (!list)
// 	{
// 		printf ("NULL\n");
// 		return (0);
// 	}
// 	elem = list->begin;
// 	while (elem->next)
// 	{
// 		printf ("type_str= %d  ---------          ", elem->type);
// 		printf("str_of_arr = %s\n", elem->value);
// 		elem = elem->next;
// 	}
// 	printf ("type_str= %d  ---------          ", elem->type);
// 	printf("str_of_arr = %s\n", elem->value);

// 	return (0);
// }
