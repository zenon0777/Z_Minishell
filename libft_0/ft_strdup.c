/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 01:18:22 by adaifi            #+#    #+#             */
/*   Updated: 2021/11/26 03:21:26 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*cpy;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	cpy = malloc(len + 1);
	if (!(cpy))
		return (NULL);
	while (i < (len + 1))
	{
		((unsigned char *)cpy)[i] = ((unsigned char *)s1)[i];
		i++;
	}
	((unsigned char *)cpy)[i] = '\0';
	return (cpy);
}
