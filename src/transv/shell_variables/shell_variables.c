/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:10:04 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/16 15:07:54 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "error.h"
#include "shell_variables.h"
#include "parser_utils_shvar.h"

struct s_btree	*g_shellvariables;

int     add_variable(struct s_assign *var)
{
    ft_printf("name:%s\nvalue:%s\nindex:%llu\nhasindex:%d\n\n", var->name, var->value, var->index, var->hasindex);

    return (e_success);
}