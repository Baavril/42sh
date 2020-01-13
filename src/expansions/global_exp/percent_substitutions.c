/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitutions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/08 13:58:54 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

static int
	check_percent_var(char **token, char *word, struct s_svar *tmp, int flag)
{
	char	*value;

	value = NULL;
	if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0
	&& check_next_var(g_svar->key, token, 1) == SUCCESS)
	{
		free(*token);
		if (!(value = ft_strdup(g_svar->value)))
			return (ERROR);
		*token = matching_ret(ft_strrev(value), word, flag);
		*token = ft_strrev(*token);
		g_svar = tmp;
		ft_strdel(&word);
		return (SUCCESS);
	}
	return (ERROR);
}

int
	opercent_exp(char **token)
{
	int				flag;
	char			*word;
	struct s_svar	*tmp;

	tmp = g_svar;
	flag = (!(ft_spechrlen(*token))) ? 2 : 1;
	word = ft_strcdup(ft_strchr(*token, PERCENT) + flag, CL_BRACE);
	while (g_svar)
	{
		if (check_percent_var(token, word, tmp, flag) == SUCCESS)
			return (SUCCESS);
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	if (!(*token = ft_strdup(EMPTY_STR)))
		return (ERROR);
	g_svar = tmp;
	return (SUCCESS);
}
