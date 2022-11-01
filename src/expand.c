/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 21:46:18 by adaifi            #+#    #+#             */
/*   Updated: 2022/10/31 01:11:59 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../trees.h"

char *d_expand(char *input, t_env *env)
{
    char *tmp;
    char *value;

    while (*input)
    {
        if (*input == '$')
        {
            input++;
            value = check_expand(*input, env);
        }
        *tmp = *input;
        input++;
        tmp++;
    }
}