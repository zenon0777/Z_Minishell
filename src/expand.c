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
    // if (ret == false)
    //     exit (0);
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
        return 0;
	ft_free((void **)(&value));
	return (expand_brace(brace));
}
char    quotes_type(char *arg)
{
    char    key = '\0';
    char    *tmp;
    int        i;

    tmp = arg;
    i = 0;
    while (tmp[i])
    {
        if (tmp[i] == '\"' || tmp[i] == '\'')
        {
            if (tmp[i] == '\"')
                key = 34;
            else
                key = 39;
            break;
        }
        i++;
    }
    return (key);
}

char    *removeChar(char *arg)
{
    char    key;
    char    **table;
    char    *fermer = NULL;
    char    *tmp0;
   

    tmp0 = NULL;
    table = (char **)malloc(sizeof(char *) * 6);
    if (!table)
        return (NULL);
    while (1)
    {
        key = quotes_type(arg);
        table[1] = ft_strchr(arg, key);
        table[2] = ft_strchr(table[1] + 1, key) + 1;
        tmp0 = ft_substr(arg, 0, table[1] - arg);
        table[3] = ft_substr(arg, (table[1] - arg), (table[2] - table[1]));
        table[4] = ft_strtrim(table[3], &key);
        table[5] = ft_strjoin(tmp0, table[4]);
		free(tmp0);
        if (!fermer)
            fermer = ft_strdup(table[5]);
        else
            fermer = ft_strjoin_custom(fermer, table[5]);
        arg = table[2];
        free(table[3]);
        free(table[5]);
        free(table[4]);
        if (!*(table[2] + 1))
            break;
    }
    free(table);
    return (fermer);
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
