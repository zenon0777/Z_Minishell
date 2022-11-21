/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:04:11 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/20 20:59:41 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	env_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
		{
			if (tmp && tmp->key && ft_strcmp(tmp->value, "\0"))
				printf("%s=%s\n", tmp->key, tmp->value);
			else if (tmp && tmp->key && !ft_strcmp(tmp->value, "\0"))
				ft_putendl_fd(tmp->key, 0);
		}
		tmp = tmp->next;
	}
}
