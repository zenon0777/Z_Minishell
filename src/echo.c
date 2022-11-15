/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:06:02 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/15 10:29:06 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../minishell.h"
void	echo(t_list *arg)
{
	char	**s;
	int		i;
	int		k;

	i = 0;
	if (arg && (!arg->next || !ft_strcmp(arg->next->content, "\0")))
		return (ft_putendl_fd("", 1));
	s = join_echo(&arg);
	k = check_newline(s);
	i = k;
	if (i > 0)
	{
		while (s[i])
		{
			ft_putstr_fd(s[i], 1);
			ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (k == 0)
		echo_newline(s);
	ft_free_2d(s);
}

void	echo_newline(char **s)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup("");
	while (s[i])
	{
		str = ft_strjoin(str, s[i]);
		str = ft_strjoin(str, " ");
		i++;
	}
	printf("%s\n", str);
	free(str);
}

char	**join_echo(t_list **arg)
{
	char	*output;
	char	**s;

	output = ft_strdup("");
	while ((*arg)->next)
	{
		if (!ft_strcmp((*arg)->next->content, "|"))
		{
			s = ft_split(output, ' ');
			return (s);
		}
		output = ft_strjoin(output, (*arg)->next->content);
		output = ft_strjoin(output, " ");
		(*arg) = (*arg)->next;
	}
	s = ft_split(output, ' ');
	free(output);
	return (s);
}

int	check_newline(char **str)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	j = 1;
	while (str[i])
	{
		while (str[i][0] == '-' && str[i][j] == 'n')
		{
			j++;
			if (!str[i][j])
				k += 1;
		}
		i++;
	}
	return (k);
}
