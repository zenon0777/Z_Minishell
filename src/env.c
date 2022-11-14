/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:04:11 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/14 09:00:45 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	env_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (strcmp(tmp->value, "\0") != 0)
		{
			if (tmp && tmp->key && tmp->value)
				printf("%s=%s\n", tmp->key, tmp->value);
		}
		tmp = tmp->next;
	}
}
