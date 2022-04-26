/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 18:49:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/12 14:41:15 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/processes.h"

// Get absolute path.
// "dir_name" + "file_name" = /dir_name/file_name.
// May return NULL
static char	*proc_get_full_path(char *dir, char *file_name)
{
	char	*res;
	char	*tmp;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, file_name);
	free(tmp);
	if (!res)
		return (NULL);
	return (res);
}

// Get PATH string from enviroment
// and convert it to the array of paths to directories.
// May return NULL
char	**proc_get_paths_array(char **envp)
{
	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (*envp && ft_strlen(*envp) > 4 && !ft_strncmp(*envp, "PATH", 4))
		{
			return (ft_split(*envp + 5, ':'));
		}
		envp++;
	}
	return (NULL);
}

// Find path to the executable file [file_name]
// in the list of directories [dirs].
// May return NULL
static char	*proc_find_PATH_exec(char **dirs, char *file_name)
{
	int		iter;
	char	*path;

	if (!dirs || !file_name)
		return (NULL);
	iter = 0;
	while (*(dirs + iter))
	{
		path = proc_get_full_path(*(dirs + iter), file_name);
		if (!path)
			return (NULL);
		if (!access(path, 1))
			return (path);
		iter++;
		free(path);
	}
	return (NULL);
}

// Check if [cmd] is bash command or path.
// Return path to the executable file.
// May return NULL
char	*proc_parse_cmd(char *cmd)
{
	char	*path;
	char	**dirs;
	char	**envp;

	if (!cmd || !ft_strlen(cmd))
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	envp = env_get_content(g_data.envp, 0);
	dirs = proc_get_paths_array(envp);
	path = proc_find_PATH_exec(dirs, cmd);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		g_data.exit_status = 127;
	}
	utils_destroy_strings_array(envp);
	utils_destroy_strings_array(dirs);
	return (path);
}
