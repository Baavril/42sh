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

#include <unistd.h>

#include "libft.h"
#include "error.h"
#include "shell_variables.h"
#include "parser_utils_shvar.h"

/* expansion like module to get assignement in tokens or str ? */

static __inline__ int  simple_assignement(struct s_assign *var, char *str)
{
    var->value = get_value(str);
    if (var->value)
    {
            var->name = get_name(str);
            ft_setenv(var->name, var->value, 1); /* using setenv as a test */
            ft_memdel((void**)&(var->name));
    }
    return (e_success);
}

static __inline__ int   indexed_assignement(struct s_assign *var, char *str)
{
    var->value = get_value(str);
    var->index |= 1;
    ft_printf("okokokokoko\n");
    if (contains_array_subscript(var->value))
    {
        ft_dprintf(STDERR_FILENO, "%s: %s: cannot assign list to array member", g_progname, var->name);
        return (e_cannot_assign_list_to_array_member);
    }
    ft_printf("%s > %llu\n", var->value, get_index(str));
    return (e_success);
}

int     assign_variable(char *str)
{
    struct s_assign var;
    int ret;

    var = (struct s_assign){0};
    if (!str)
        return (e_invalid_input);
    ret = is_format_legit(str);
    if (ret == ISLEGIT)
        return (simple_assignement(&var, str));
    else if (ret == HASINDEX)
        return (indexed_assignement(&var, str));
    return (e_success);
}
