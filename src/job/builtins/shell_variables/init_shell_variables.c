/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:10:04 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/16 16:57:16 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "error.h"
#include "shell_variables.h"

struct s_shvar	*g_shellvar = NULL;

static int	init_shvar(const char *name, const char *const content)
{
	g_shellvar = (struct s_shvar*)ft_memalloc(sizeof(struct s_shvar));
	if (!g_shellvar)
	{
		return (e_cannot_allocate_memory);
	}
	g_shellvar->value = ft_strdup(name);
	g_shellvar->next_content = (struct s_shvar*)ft_memalloc(
					sizeof(struct s_shvar));
	if (!g_shellvar->next_content)
	{
		return (e_cannot_allocate_memory);
	}
	g_shellvar->next_content->value = ft_strdup(content);
	g_shellvar->index = 0;
	g_shellvar->next_var = NULL;
	return (e_success);
}

int		initialize_shell_variables(char *argv)
{
	int	ret;

	ret = init_shvar("_", argv);
	if (ret)
	{
		ft_dprintf(STDERR_FILENO,
				"Could not assign minimal shell variables\n");
	}
	return (ret);
}
