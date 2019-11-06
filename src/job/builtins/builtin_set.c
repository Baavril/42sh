/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/14 15:22:09 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell_variables.h"
#include "ft_getopt.h"
#include "libft.h"
#include "error.h"

static void	display_shvar(void)
{
	extern struct s_shvar	*g_shellvar;
	struct s_shvar		*ptr;
	struct s_shvar		*inside;

	ptr = g_shellvar;
	while (ptr)
	{
		ft_printf("%s=", ptr->value);
		if (ptr->index == 0 && ptr->next_content && ptr->next_content->value)
		{
			/* display litteral value */
			ft_printf("%s\n", ptr->next_content->value);
		}
		else if (ptr->index)
		{
			/* display array */
			ft_printf("(");
			inside = ptr->next_content;
			while (inside)
			{
				ft_printf("[%llu]=\"%s\" ", inside->index, inside->value);
				inside = inside->next_content;
			}
			ft_printf(")\n");
		}
		ptr = ptr->next_var;
	}
}

int		cmd_set(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (argc == 1)
	{
		display_shvar();
	}
	return (e_success);
}
