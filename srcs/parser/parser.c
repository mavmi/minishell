#include "../../include/parser.h"

static int	substr_count(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (-1);
	while (cmd[i] != ' ' && cmd[i] != *REDIR_INP1_S
				&& cmd[i] != *REDIR_INP2_S && cmd[i] != *REDIR_PIPE_S
				&& cmd[i])
		i++;
	return (i);
}

static int	elem_counter(char *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == *REDIR_INP1_S || cmd[i] == *REDIR_INP2_S
				|| cmd[i] == *REDIR_PIPE_S)
		{
			if ((cmd[i+1] == *REDIR_INP1_S && cmd[i] == *REDIR_INP1_S)
					|| (cmd[i+1] == *REDIR_INP2_S && cmd[i] == *REDIR_INP2_S))
				i++;
			count++;
			i++;
		}
		else if (cmd[i] != ' ')
		{
			while (cmd[i] != ' ' && cmd[i] != *REDIR_INP1_S
						&& cmd[i] != *REDIR_INP2_S && cmd[i] != *REDIR_PIPE_S
						&& cmd[i])
				i++;
			count++;
		}
		while (cmd[i] == ' ')
			i++;
	}
	return (count);
}

static char	*get_elem(char *cmd)
{
	static int	i = 0;
	int			j;
	int			str_count;
	char		*return_str;

	return_str = NULL;
	j = 0;
	str_count = 0;
	while (1)
	{
		if (cmd[i] == *REDIR_INP1_S || cmd[i] == *REDIR_INP2_S
				|| cmd[i] == *REDIR_PIPE_S)
		{
			return_str = (char *)malloc(sizeof(char) * 3);
			return_str[j] = cmd[i++];
			if ((cmd[i] == *REDIR_INP1_S && cmd[i - 1] == *REDIR_INP1_S)
					|| (cmd[i] == *REDIR_INP2_S && cmd[i - 1] == *REDIR_INP2_S))
			{
				return_str[++j] = cmd[i++];
			}
			return_str[++j] = '\0';
			return (return_str);
		}
		else if (cmd[i] != ' ' && cmd[i])
		{
			str_count = substr_count(cmd + i);
			return_str = (char *)malloc(sizeof(char) * (str_count + 1));
			if (!return_str || str_count == -1)
				return (NULL);
			while (cmd[i] != ' ' && cmd[i] != *REDIR_INP1_S
						&& cmd[i] != *REDIR_INP2_S && cmd[i] != *REDIR_PIPE_S
						&& cmd[i])
				return_str[j++] = cmd[i++];
			return_str[j] = '\0';
			return (return_str);
		}
		while (cmd[i] == ' ')
			i++;
		if (!cmd[i])
			return (NULL);
	}
		return (NULL);
}

char	**par_split(char *cmd, char **redirect)
{
	int		i;
	char	**elem_arr;
	char	*elem;

	i = 0;
	elem_arr = (char **)malloc((elem_counter(cmd) + 1) * (sizeof(char *)));
	elem = get_elem(cmd);
	if (!cmd || !redirect || !elem_counter || !elem)
		return (NULL);
	while (elem)
	{
		elem_arr[i] = elem;
		i++;
		elem = get_elem(cmd);
	}
	elem_arr[i] = NULL;
	return (elem_arr);
}
