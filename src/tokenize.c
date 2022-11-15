# include "../minishell.h"

char	*tokenize_internal(char *input, char *begin, char *end, t_list **chunks)
{
	char	*token;
	t_list	*temp;

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
			begin = tokenize_internal(input, begin, end, chunks);
	}
}