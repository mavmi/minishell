/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 18:49:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/08 16:22:49 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

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
// and convert it to the array of stirngs.
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
char	*proc_find_executable(char **dirs, char *file_name)
{
	int		iter;
	char	*path;

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
