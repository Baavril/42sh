/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignement_shellvar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:04:10 by abarthel          #+#    #+#             */
/*   Updated: 2019/11/08 10:04:43 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "shell_variables.h"
#include "parser_utils_shvar.h"

/* expansion like module to get assignement in tokens or str ? */

int     assign_variable(char *str)
{
    char *ptr;
    int ret;

    if (!str)
        return (e_invalid_input);
    ret = is_format_legit(str);
    if (ret == ISLEGIT)
    {
        ptr = ft_strstr(str, "=");
        *ptr = '\n';
        ++ptr;
        if (*ptr)
            ft_setenv(str, ptr, 1); /* using setenv as a test */
        --ptr;
        *ptr = '=';
    }
    else if (ret == HASINDEX)
    {
        return (e_success);
    }
    return (e_success);
}
