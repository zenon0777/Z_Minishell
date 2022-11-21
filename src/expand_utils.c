/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimzaoua <yimzaoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:56:31 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/21 16:14:36 by yimzaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*quotes_type(char *arg)
{
	char	*tmp;
	int		i;

	tmp = arg;
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
		{
			if (tmp[i] == '\"')
				return (ft_strdup("\""));
			else
				return (ft_strdup("\'"));
			break ;
		}
		i++;
	}
	return (ft_strdup(""));
}

int	setup_0(char **table, char *arg, char *fermer, char **key)
{
	*key = quotes_type(arg);
	if (arg)
		table[1] = ft_strchr(arg, *key);
	if (table[1][0] == '\0')
	{
		free(*key);
		free(table);
		if (*fermer == NULL)
			return (0);    // return (ft_strdup(arg))
		return (1);    // return (ft_strjoin_custom(*fermer, arg))
	}
	return (2);
}

void	setup_1(char **table, char *arg, char **key, char **fermer)
{
	char	*tmp0;

	tmp0 = NULL;
	table[2] = ft_strchr(table[1] + 1, *key) + 1;
	tmp0 = ft_substr(arg, 0, table[1] - arg);
	table[3] = ft_substr(arg, (table[1] - arg), (table[2] - table[1]));
	table[4] = ft_strtrim(table[3], key);
	table[5] = ft_strjoin_custom(tmp0, table[4]);
	if (!*(fermer))
		fermer = ft_strdup(table[5]);
	else
		fermer = ft_strjoin_custom(fermer, table[5]);
	free(*key);
}

char	*removechar(char *arg)
{
	char	*key;
	char	**table;
	char	*fermer;
	char	*tmp0;

	fermer = NULL;
	table = (char **)malloc(sizeof(char *) * 6);
	if (!table)
		return (NULL);
	while (1)
	{
		// key = quotes_type(arg);
		// if (arg)
		// 	table[1] = ft_strchr(arg, *key);
		// if (table[1][0] == '\0')
		// {
		// 	if (fermer == NULL)
		// 		return (free(key), free(table), ft_strdup(arg));
		// 	return (free(key), free(table), ft_strjoin_custom(fermer, arg));
		// }
		if (setup_0(table, arg, fermer, &key) == 0)
			return (ft_strdup(arg));
		else if (setup_0(table, arg, fermer, &key) == 1)
			return (ft_strjoin_custom(*fermer, arg));
		// table[2] = ft_strchr(table[1] + 1, *key) + 1;
		// tmp0 = ft_substr(arg, 0, table[1] - arg);
		// table[3] = ft_substr(arg, (table[1] - arg), (table[2] - table[1]));
		// table[4] = ft_strtrim(table[3], key);
		// table[5] = ft_strjoin_custom(tmp0, table[4]);
		// if (!fermer)
		// 	fermer = ft_strdup(table[5]);
		// else
		// 	fermer = ft_strjoin_custom(fermer, table[5]);
		arg = table[2];
		free(table[3]);
		free(table[5]);
		free(table[4]);
		free(key);
		if (!*(table[2] + 1))
			break ;
	}
	return (free(table), fermer);
}

char	*expand_internal(char *input, char *it, bool d_quote, t_env *envmap)
{
	char	*first;
	char	*last;
	char	*middle;
	char	*former;
	char	*latter;

	first = ft_substr(input, 0, it - input);
	last = expand_last(it + 1);
	middle = expand_middle(input, it, last, envmap);
	last = ft_strdup(last);
	former = ft_strjoin(first, middle);
	latter = expand(last, envmap, d_quote);
	ft_free((void **)(&middle));
	ft_free((void **)(&first));
	free(input);
	input = ft_strjoin(former, latter);
	ft_free((void **)(&latter));
	ft_free((void **)(&former));
	return (input);
}

char	*expand(char *input, t_env *envmap, bool d_quote)
{
	char	*iter;

	if (input == NULL)
		return (NULL);
	iter = input;
	while (*iter)
	{
		if (*iter == '\"')
			d_quote = !d_quote;
		else if (*iter == '\'' && !d_quote)
			iter = ft_strchr(iter + 1, '\'');
		else if (*iter == '<' && *(iter + 1) == '<' && !d_quote)
		{
			iter += 2;
			while (*iter && ft_isspace(*iter))
				++iter;
			while (*iter && !ft_isspace(*iter))
				++iter;
		}
		if (*iter == '$')
			return (expand_internal(input, iter, d_quote, envmap));
		if (*iter)
			++iter;
	}
	return (input);
}
