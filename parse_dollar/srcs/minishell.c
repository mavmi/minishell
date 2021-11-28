/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:54:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/28 19:10:46 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/enviroment.h"

// gcc -Wall -Wextra -Werror srcs/*/*.c srcs/minishell.c libft/libft.a -o minishell.out

static size_t	par_get_arr_len(char **array)
{
	size_t	len;

	if (!array)
		return (0);
	len = 0;
	while (*array)
	{
		len++;
		array++;
	}
	return (len);
}

static char	*par_handle_vars(char *substr)
{
	char		*ptr;
	char		*var_name;
	char		*output;
	char		*tmp;
	t_env_elem	*env_elem;

	if (!substr)
		return (NULL);
	output = NULL;
	while (*substr)
	{
		if (*substr != '$')
		{
			ptr = ft_strchr(substr, '$');
			if (!ptr)
			{
				utils_append_string(&output, substr);
				break ;
			}
			tmp = ft_substr(substr, 0, ptr - substr);
			utils_append_string(&output, tmp);
			substr += ft_strlen(tmp);
			free(tmp);
		}
		else if (*(substr + 1) == ' ' || *(substr + 1) == 0)
		{
			utils_append_string(&output, "$");
			substr++;
		}
		else
		{
			substr++;
			ptr = ft_strchr(substr, ' ');
			if (ptr)
				var_name = ft_substr(substr, 0, ptr - substr);
			else
				var_name = ft_strdup(substr);
			env_elem = env_get_by_name(g_data.envp, var_name);
			if (env_elem)
				utils_append_string(&output, env_elem->value);
			else if (utils_cmp_strings(var_name, "?"))
			{
				tmp = ft_itoa(g_data.exit_status);
				utils_append_string(&output, tmp);
				free (tmp);
			}
			else
				utils_append_string(&output, "");
			substr += ft_strlen(var_name);
			free(var_name);
		}
	}
	return (output);
}

static char	*par_handle_str(char *cmd)
{
	char	*quote_1;
	char	*quote_2;
	char	*output;
	char	*substr;
	char	*parsed_substr;	

	if (!cmd)
		return (NULL);
	output = NULL;
	while (*cmd)
	{
		if (*cmd != '\'' && *cmd != '\"')
		{
			quote_1 = ft_strchr(cmd, '\'');
			quote_2 = ft_strchr(cmd, '\"');
			if (!quote_1 && !quote_2)
				substr = ft_strdup(cmd); 
			else if (quote_1 && !quote_2)
				substr = ft_substr(cmd, 0, quote_1 - cmd);
			else if (!quote_1 && quote_2)
				substr = ft_substr(cmd, 0, quote_2 - cmd);
			else
			{
				if (quote_2 < quote_1)
					quote_1 = quote_2;
				substr = ft_substr(cmd, 0, quote_1 - cmd);
			}
			parsed_substr = par_handle_vars(substr);
			cmd += ft_strlen(substr);
		}
		else
		{
			quote_1 = ft_strchr(cmd + 1, *cmd);
			if (!quote_1)
				return (NULL);
			else
				substr = ft_substr(cmd, 1, quote_1 - cmd - 1);
			if (*cmd == '\"')
				parsed_substr = par_handle_vars(substr);
			else
				parsed_substr = ft_strdup(substr);
			cmd += ft_strlen(substr) + 2;
		}
		utils_append_string(&output, parsed_substr);
		free(substr);
		free(parsed_substr);
	}
	return (output);
}

char	**par_handle_array(char **commands)
{
	int		iter;
	char	**output;

	if (!commands)
		return (NULL);
	output = (char **)malloc(sizeof(char *) * (par_get_arr_len(commands) + 1));
	if (!output)
		return (NULL);
	iter = 0;
	while (commands[iter])
	{
		output[iter] = par_handle_str(commands[iter]);
		if (!output[iter])
		{
			while (iter >= 0)
				free(output[iter--]);
			free(output);
			return (NULL);
		}
		iter++;
	}
	output[iter] = NULL;
	return (output);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc; (void)argv;
	g_data.envp = env_create(envp);

	env_push_back(g_data.envp, "var=123");
	
	char *str = par_handle_str("oba");
	printf("%s\n", str);
	free(str);

	env_destroy(g_data.envp);
}
