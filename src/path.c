/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:06:13 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/14 17:43:38 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	*get_path(char *cmd, t_env **env)
{
	char	**paths;
	char	*path;
	int		i;
	char	*tmp;

	i = -1;
	paths = NULL;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	paths = search_path(env, paths);
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		if (path == NULL)
			return (ft_free_2d(paths), free(tmp), NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_2d(paths), path);
	}
	ft_free_2d(paths);
	return (NULL);
}

char	**search_path(t_env **env, char	**paths)
{
	while ((*env))
	{
		if (!ft_strcmp((*env)->key, "PATH"))
			paths = ft_split((*env)->value, ':');
		(*env) = (*env)->next;
	}
	return (paths);
}
