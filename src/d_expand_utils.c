/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_expand_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 00:46:51 by adaifi            #+#    #+#             */
/*   Updated: 2022/10/31 01:07:17 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../trees.h"

char *check_expand(char *str, t_env *env)
{
    char *tmp;

    tmp = ft_strdup("");
    while(*str)
    {
        if (!ft_isalpha(str[0]))
            ++str;
        if (*str >= 'A' && *str <= 'Z')
            *tmp = *str;
        if (ft_isalnum(*str) && (*str >= 'a' && *str <= 'z'))
            break ;
        str++;
    }
    while (env)
    {
        if (!strcmp(env->key, tmp))
        {
            tmp = env->value;
            return tmp;
        }
        env = env->next;
    }
    return (NULL);
}