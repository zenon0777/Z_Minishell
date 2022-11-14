#include "../minishell.h"

void	ft_free(void **ptr)
{
	if (!(ptr && *ptr))
		return ;
	free(*ptr);
	*ptr = NULL;
}

bool	ft_strappend(char **s, char *s2)
{
	char	*s1;

	if (!*s)
	{
		*s = ft_strdup(s2);
		if (!*s)
			return (false);
		return (true);
	}
	s1 = ft_strdup(*s);
	if (!s1)
		return (false);
	ft_free((void **)s);
	if (!ft_calloc0((void **)s, ft_strlen(s1) + ft_strlen(s2) + 1, 1))
	{
		ft_free((void **)(&s1));
		return (false);
	}
	ft_strlcpy(*s, s1, ft_strlen(s1) + 1);
	ft_strlcpy(*s + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	ft_free((void **)(&s1));
	return (true);
}

bool	ft_isspace(int c)
{
	return (c == ' ' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f' || c == '\t');
}

bool	ft_calloc0(void **ptr, size_t cnt, size_t n)
{
	*ptr = (void *)malloc(cnt * n);
	if (!*ptr)
		return (false);
	ft_memset(*ptr, 0, cnt * n);
	return (true);
}