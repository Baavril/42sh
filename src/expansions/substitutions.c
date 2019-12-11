/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitutions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2019/11/09 11:47:27 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "shell_variables.h"
#include "libft.h"

int		direct_exp(char **token)
{
	struct s_svar *tmp;

	tmp = g_svar;
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 1, ft_strlen(g_svar->key) - 1) == 0)
		{
			ft_strdel(token);
			*token = ft_strdup(g_svar->value);
			g_svar = tmp;
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	g_svar = tmp;
	return (ERROR);
}

int		simple_exp(char **token)
{
	struct s_svar *tmp;

	tmp = g_svar;
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0)
		{
			ft_strdel(token);
			*token = ft_strdup(g_svar->value);
			g_svar = tmp;
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	g_svar = tmp;
	return (ERROR);

}

int		why_exp(char **token)
{
	(void)token;

	ft_printf("why success");
	return (SUCCESS);
}

int		plus_exp(char **token)
{
	(void)token;

	ft_printf("plus success");
	return (SUCCESS);
}

int		dash_exp(char **token)
{
	(void)token;

	ft_printf("dash success");
	return (SUCCESS);
}

int		equal_exp(char **token)
{
	(void)token;

	ft_printf("equal success");
	return (SUCCESS);
}

int		bsharp_exp(char **token)
{
	struct s_svar *tmp;

	tmp = g_svar;
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 3, ft_strlen(g_svar->key) - 1) == 0)
		{
			ft_strdel(token);
			*token = ft_itoa(ft_strlen(g_svar->value));
			g_svar = tmp;
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	g_svar = tmp;
	return (ERROR);
}

int		osharp_exp(char **token)
{
	(void)token;

	ft_printf("osharp success");
	return (SUCCESS);
}

int		dsharp_exp(char **token)
{
	(void)token;

	ft_printf("dsharp success");
	return (SUCCESS);
}

int		opercent_exp(char **token)
{
	(void)token;

	ft_printf("opercent success");
	return (SUCCESS);
}

int		dpercent_exp(char **token)
{
	(void)token;

	ft_printf("dpercent success");
	return (SUCCESS);
}
