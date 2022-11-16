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
			break;
		}
		tmp = tmp->next;
	}
	return(value);
}

char	*expand_last(char *it)
{
	if (*it && ft_strchr("$?", *it))
		++it;
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
        // if (append != NULL && append->content != NULL)
        //     exit(0); 
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
    if (ret == false)
        exit (0);
	while (brace->next != NULL)
	{
		brace = brace->next;
		ret = ft_strappend(&middle, " ");
		// if (ret == false)
        //     exit (0); 
		ret = ft_strappend(&middle, (char *)(brace->content));
		// if (ret == false)
        //     exit (0); 
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
	value = getvalue(key, envmap);
	if (value == NULL)
		value = "";
	ft_free((void **)(&key));
	value = ft_strdup(value);
	if (value == NULL || !*value)
		return (value);
	expand_space(value, &brace);
    if (brace == NULL)
        return 0;
	ft_free((void **)(&value));
	return (expand_brace(brace));
}

char	*removeChar(char *str)
{
    int		i;
	int		j;
    int		len;
    char	*tmp;

	len = strlen(str);
    tmp = ft_strdup(str);
	i = 0;
	while (i < len)
	{
		while (tmp[i] == '\'')
		 	i++;
		if (tmp[i] == '\"')
		{
			j = i;
			while (j < len)
			{
				tmp[j] = tmp[j + 1];
				j++;
			}
			len--;
			i--;
		}
		i++;
	}
    return(tmp);
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
	latter = expand(last,envmap ,d_quote);
	ft_free((void **)(&middle));
	ft_free((void **)(&first));
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
