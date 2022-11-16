/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:06:02 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/16 22:57:47 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../minishell.h"
void	echo(t_list *arg)
{
	char	*tmp;
	int		i;
	// int		k;

	i = 0;
	if (arg && (!arg->next || !ft_strcmp(arg->next->content, "\0")))
		return (ft_putendl_fd("", 1));
	tmp = join_echo(&arg);
	// k = check_newline(lst->next->content);
	i = 0;
	// if (i > 0)
		printf("%s\n", tmp);
	// else (k == 0)
	// 	echo_newline(tmp);
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
		if (s[i + 1])
			str = ft_strjoin(str, " ");
		i++;
	}
	printf("%s\n", str);
	free(str);
}

char	*join_echo(t_list **arg)
{
	char	*output;

	output = ft_strdup("");
	if (*arg)
		(*arg) = (*arg)->next;
	while ((*arg))
	{
		(*arg)->content = removeChar((*arg)->content);
		if (!ft_strcmp((*arg)->content, ">"))
		{
			(*arg) = (*arg)->next->next;
			if ((*arg) == NULL)
				break ;
		}
		if (!ft_strcmp((*arg)->content, "|"))
			return (output);
		output = ft_strjoin(output, (*arg)->content);
		if ((*arg)->next)
			output = ft_strjoin(output, " ");
		(*arg) = (*arg)->next;
	}
	return (output);
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
