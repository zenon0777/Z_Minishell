/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 02:24:17 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/20 22:15:08 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	i;
	size_t	len1;
	size_t	index;

	i = 0;
	len1 = ft_strlen(s);
	if (!s)
		return (NULL);
	if (len1 < len)
		len = ft_strlen(s);
	s1 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s1)
		return (NULL);
	index = start;
	while (index < len1 && i < len)
	{
		s1[i] = s[index++];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
