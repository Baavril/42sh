/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitutions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/26 17:41:38 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

extern struct s_svar	*g_svar;

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
		*token = ft_strdup(matching_ret(ft_strrev(value), word, flag));
		*token = ft_strrev(*token);
		g_svar = tmp;
		ft_strdel(&word);
		ft_strdel(&value);
		return (SUCCESS);
	}
	return (ERROR);
}

char	*ft_revstar(char *word)
{
	int i;
	int len;
	int flag;
	char *tmp1;

	i = 0;
	flag = 0;
	tmp1 = NULL;
	len = (int)ft_strlen(word) - 1;
	if (!(tmp1 = (char*)ft_memalloc(sizeof(char) * (len + 2))))
		return (NULL);
	while (len - 1 >= -1)
	{
		while (word[len] == CL_SQUAR)
		{
			while (word[len] != OP_SQUAR)
				--len;
			while (word[len] != CL_SQUAR)
			{
				tmp1[i] = word[len];
				++i;
				++len;
			}
			tmp1[i] = word[len];
			while (word[len] != OP_SQUAR)
				--len;
			if (len - 1 > -1)
			{
				--len;
				++i;
			}
			else if (len == 0 && word[len] == OP_SQUAR)
				flag++;
		}
		if (flag)
			break;
		tmp1[i] = word[len];
		++i;
		--len;
	}
	ft_strdel(&word);
	return (tmp1);
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
	if (ft_isin(OP_SQUAR, word) && ft_isin(CL_SQUAR, word))
		word = ft_revstar(word);
	else
		ft_strrev(word);
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
	ft_strdel(&word);
	return (SUCCESS);
}
