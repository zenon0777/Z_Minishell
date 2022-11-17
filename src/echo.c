/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:06:02 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/17 22:20:16 by adaifi           ###   ########.fr       */
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
	tmp = join_echo(arg);
	if (arg->flag == 1)
	{
		ft_putstr_fd(tmp, 1);
		return ;
	}
	printf("%s\n", tmp);
}

char	*join_echo(t_list *arg)
{
	char	*output;
	char	*tmp;

	output = ft_strdup("");
	if (arg)
		arg = arg->next;
	if ((check_newline(arg->content) == 0))
	{
		arg->flag = 1;
		arg = arg->next;
	}
	while (arg)
	{
		tmp = removeChar(arg->content);
		if ((!ft_strcmp(tmp, ">")))
		{
			arg = arg->next->next;
			if (arg == NULL)
				break ;
		}
		if (!ft_strcmp(tmp, "|"))
			return (output);
		output = ft_strjoin(output, tmp);
		if (arg->next)
			output = ft_strjoin(output, " ");
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
				return (0);
		}
		i++;
	}
	return (1);
}
