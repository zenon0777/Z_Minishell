/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:54:05 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/20 18:54:06 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getvalue(char *key, t_env *envmap)
{
	t_env	*tmp;
	char	*value;

	tmp = envmap;
	value = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			value = tmp->value;
			break ;
		}
		tmp = tmp->next;
	}
	return (value);
}

char	*expand_last(char *it)
{
	if (*it && ft_strchr("$?", *it))
	{
		if (ft_strchr("$?", *it))
		++it;
	}
	else
		while (*it && ft_isalnum(*it))
			++it;
	return (it);
}

void	expand_space(char *value, t_list **brace)
{
	t_list	*append;
	char	*search;

	*brace = NULL;
	search = value;
	append = NULL;
	while (true)
	{
		search = ft_strchr(value, ' ');
		if (search == NULL)
			break ;
		*search++ = '\0';
		append = ft_lstnew(ft_strdup(value));
		value = search;
		ft_lstadd_back(brace, append);
	}
	if (!*value)
		return ;
	append = ft_lstnew(ft_strdup(value));
	if (append == NULL && append->content == NULL)
		return ;
	ft_lstadd_back(brace, append);
}

char	*expand_brace(t_list *brace)
{
	bool	ret;
	char	*middle;
	t_list	*origin;

	middle = NULL;
	origin = brace;
	ret = ft_strappend(&middle, (char *)(brace->content));
	while (brace->next != NULL)
	{
		brace = brace->next;
		ret = ft_strappend(&middle, " ");
		ret = ft_strappend(&middle, (char *)(brace->content));
	}
	ft_lstclear(&origin, (void *)free);
	return (middle);
}

char	*expand_middle(char *input, char *it, char *last, t_env *envmap)
{
	char	*key;
	char	*value;
	t_list	*brace;

	if (last - it == 1)
		return (ft_strdup("$"));
	key = ft_substr(input, it - input + 1, last - it - 1);
	if (!ft_strcmp(key, "?"))
		return (ft_strdup(ft_itoa(var.exit_status)));
	value = getvalue(key, envmap);
	if (value == NULL)
		value = "";
	ft_free((void **)(&key));
	value = ft_strdup(value);
	if (value == NULL || !*value)
		return (value);
	expand_space(value, &brace);
	if (brace == NULL)
		return (0);
	ft_free((void **)(&value));
	return (expand_brace(brace));
}
