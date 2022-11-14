/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:42:09 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/14 17:20:41 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	her_doc(t_list *arg)
{
	char	*s;
	int	file;
	int	tmp;

	file = open("/tmp/tmpfile", O_WRONLY | O_CREAT | O_TRUNC, 00777);
	tmp = dup(file);
	s = readline(">");
	if (s == NULL || !ft_strcmp(s, arg->content))
		return (free(s), file);
	s = ft_strjoin(s, "\n");
	write(tmp, s, ft_strlen(s));
	while (ft_strcmp(s, arg->content))
	{
		free(s);
		s = readline(">");
		if (s == NULL || !ft_strcmp(s, arg->content))
			return (free(s), file);
		s = ft_strjoin(s, "\n");
		write(tmp, s, ft_strlen(s));
	}
	free(s);
	return (file);
}
