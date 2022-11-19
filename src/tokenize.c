/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:51:59 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/19 01:02:55 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*tokenize_inter(char *input, char *begin, char *end, t_list **chunks)
{
	char	*token = NULL;
	t_list	*temp;

	if (token)
		free(token);
	token = ft_substr(input, begin - input, end - begin + 1);
	temp = ft_lstnew(token);
	ft_lstadd_back(chunks, temp);
	return (end + 1);
}

void	tokenizer(char *input, t_list **chunks)
{
	char	*begin;
	char	*end;

	begin = input;
	while (*begin)
	{
		while (*begin == ' ')
			++begin;
		end = begin;
		while (*end && !ft_strchr(" ><|", *begin))
		{
			if (ft_strchr("\'\"", *end))
				end = ft_strchr(end + 1, *end);
			if (ft_strchr(" ><|", *(end + 1)))
				break ;
			++end;
		}
		if (!*end)
			--end;
		if (*begin && *begin == *(begin + 1) && ft_strchr("><", *begin))
			++end;
		if (*begin)
			begin = tokenize_inter(input, begin, end, chunks);
	}
}
