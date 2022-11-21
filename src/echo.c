/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:06:02 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/21 01:33:36 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	echo(t_list *arg)
{
	char	*tmp;
	t_list	*tmp1;
	int		i;

	i = 0;
	arg->flag = 0;
	tmp1 = arg;
	if (arg && (!arg->next || !ft_strcmp(arg->next->content, "\0")))
		return (printf("\n"), (void)arg);
	if (ft_strcmp(arg->content, "echo"))
		arg = arg->next->next;
	arg = arg->next;
	if ((check_newline(arg->content) == 0))
	{
		arg->flag = 1;
		arg = arg->next;
	}
	tmp = join_echo(arg);
	while (tmp1)
	{
		if (tmp1->flag == 1)
			return (printf("%s", tmp), free(tmp));
		tmp1 = tmp1->next;
	}
	return (printf("%s\n", tmp), free(tmp));
}

char	*join_echo(t_list *arg)
{
	char	*output;
	char	*tmp;

	output = ft_strdup("");
	while (arg)
	{
		tmp = removechar(arg->content);
		if ((!ft_strcmp(tmp, ">")) || (!ft_strcmp(tmp, ">>")))
		{
			arg = arg->next->next;
			free(tmp);
			if (arg == NULL)
				break ;
			else
				tmp = removechar(arg->content);
		}
		if (!ft_strcmp(tmp, "|"))
			return (free(tmp), output);
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
