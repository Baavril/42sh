/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 17:35:39 by baavril           #+#    #+#             */
/*   Updated: 2020/03/08 18:23:00 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"
#include "builtins.h"
#include "libft.h"
#include "expansions.h"
#include "shell_variables.h"

extern struct s_svar	*g_svar;
extern struct s_pos		*g_pos;
extern int				g_retval;

char					*get_var_value(char *var_name)
{
	char			*ret;
	struct s_svar	*voyager;

	ret = NULL;
	voyager = g_svar;
	while (voyager)
	{
		if (!ft_strncmp(var_name, voyager->str, ft_strlen(var_name)))
			ret = ft_strdup(voyager->value);
		voyager = voyager->next;
	}
	return (ret);
}

int						count_pos_params(char **token)
{
	int				i;
	struct s_pos	*ptr;

	i = 0;
	ptr = g_pos;
	while (g_pos)
	{
		++i;
		g_pos = g_pos->next;
	}
	g_pos = ptr;
	ft_strdel(token);
	*token = ft_itoa(i);
	return (SUCCESS);
}

static char				*ret_pos_params(char **token)
{
	char			*tmp;
	struct s_pos	*ptr;

	tmp = NULL;
	ptr = g_pos;
	while (g_pos)
	{
		if (ft_strncmp(g_pos->key, *token + 1, 1) == 0)
		{
			tmp = ft_strdup(g_pos->value);
			break ;
		}
		g_pos = g_pos->next;
	}
	g_pos = ptr;
	return (tmp);
}

int						reach_pos_params(char **token)
{
	char			*tmp1;
	char			*tmp2;
	int				len;

	tmp2 = NULL;
	len = ft_strlen(*token);
	tmp1 = ret_pos_params(token);
	if (ft_isin(SLASH, *token))
		len = ft_strpchr(*token, SLASH);
	if (ft_isin('"', *token))
		len = ft_strpchr(*token, '"');
	tmp2 = ft_strndup(&(*token)[ft_strpchr(*token, *(*token + 1)) + 1],
			len - 2);
	ft_strdel(token);
	*token = ft_strjoin(tmp1, tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (SUCCESS);
}

int						ret_value(char **token)
{
	ft_strdel(token);
	*token = ft_itoa(g_retval);
	return (SUCCESS);
}
