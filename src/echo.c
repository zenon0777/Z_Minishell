/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:06:02 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/19 01:41:07 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	echo(t_list *arg)
{
	char	*tmp;
	int		i;

	i = 0;
	arg->flag = 0;
	if (arg && (!arg->next || !ft_strcmp(arg->next->content, "\0")))
		return (ft_putendl_fd("", 1));
	tmp = join_echo(arg->next);
	while (arg)
	{
		if (arg->flag == 1)
		{
			ft_putstr_fd(tmp, 1);
			free(tmp);
			return ;
		}
		arg = arg->next;
	}
	printf("%s\n", tmp);
	free(tmp);
}

char	*join_echo(t_list *arg)
{
	char	*output;
	char	*tmp;

	output = ft_strdup("");
	if ((check_newline(arg->content) == 0))
	{
		arg->flag = 1;
		arg = arg->next;
	}
	while (arg)
	{
		tmp = removeChar(arg->content);
		if ((!ft_strcmp(tmp, ">")) || (!ft_strcmp(tmp, ">>")))
		{
			arg = arg->next->next;
			free(tmp);
			if (arg == NULL)
				break ;
			else
				tmp = removeChar(arg->content);
		}
		if (!ft_strcmp(tmp, "|"))
		{
			free(tmp);
			return (output);
		}
		output = ft_strjoin_custom(output, tmp);
		free(tmp);
		if (arg->next)
			output = ft_strjoin_custom(output, " ");
		arg = arg->next;
	}
	return (output);
}

int	check_newline(char *str)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_split(str, '-');
	while (tmp[i])
	{
		while (tmp[i][j] == 'n')
		{
			j++;
			if (!tmp[i][j])
			{
				ft_free_2d(tmp);
				return (0);
			}
		}
		i++;
	}
	ft_free_2d(tmp);
	return (1);
}
