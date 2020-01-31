/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_substitution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/26 20:13:10 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

extern struct s_svar	*g_svar;
extern struct s_pos		*g_pos;
int			g_retval;

static int	script_param(char **token)
{
	char	*tmp1;
	char	*tmp2;
	int		len;

	tmp1 = NULL;
	tmp2 = NULL;
	len = ft_strlen(*token);
	if (*(*token + 1) == '0')
	{
		if (ft_isin(SLASH, *token))
			len = ft_strpchr(*token, SLASH);
		tmp1 = ft_strdup("42sh");
		tmp2 = ft_strndup(&(*token)[ft_strpchr(*token, '0') + 1], len - 2);
		ft_strdel(token);
		*token = ft_strjoin(tmp1, tmp2);
		ft_strdel(&tmp1);
		ft_strdel(&tmp2);
		return (SUCCESS);
	}
	return (ERROR);
}

static int	view_pos_param(char **token)
{
	char			*tmp1;
	char			*tmp2;
	char			*tmp3;
	char			*tmp4;
	struct s_pos	*ptr;
	int				len;
	char			*esc;

	tmp1 = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	tmp4 = NULL;
	esc = " ";
	len = ft_strlen(*token);
	if (*(*token + 1) == STAR)
	{
		if (!(esc = ft_getenv("IFS")))
			esc = " ";
	}
	if (!g_pos)
		return (ERROR);
	ptr = g_pos;
	while (g_pos && g_pos->next)
	{
		tmp1 = ft_strdup(g_pos->value);
		tmp4 = (tmp2) ? NULL : ft_strjoin(tmp1, esc);
		tmp3 = (tmp2) ? tmp2 : tmp4;
		tmp2 = ft_strjoin(tmp3, g_pos->next->value);
		tmp4 = tmp2;
		tmp2 = ft_strjoin(tmp4, esc);
		g_pos = g_pos->next;
		ft_strdel(&tmp1);
		ft_strdel(&tmp3);
		ft_strdel(&tmp4);
	}
	g_pos = ptr;
	if (tmp2)
	{
		if (ft_isin(SLASH, *token))
			len = ft_strpchr(*token, SLASH);
		tmp1 = ft_strndup(&(*token)[ft_strpchr(*token, STAR) + 1], len - 2);
		ft_strdel(token);
		*token = ft_strjoin(tmp2, tmp1);
		ft_strdel(&tmp1);
		ft_strdel(&tmp2);
	}
	return (SUCCESS);
}

static int	count_pos_params(char **token)
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

static int	reach_pos_params(char **token)
{
	char			*tmp1;
	char			*tmp2;
	int				len;
	struct s_pos	*ptr;

	tmp1 = NULL;
	tmp2 = NULL;
	len = ft_strlen(*token);
	ptr = g_pos;
	while (g_pos)
	{
		if (ft_strncmp(g_pos->key, *token + 1, 1) == 0)
		{
			tmp1 = ft_strdup(g_pos->value);
			break ;
		}
		g_pos = g_pos->next;
	}
	g_pos = ptr;
	if (ft_isin(SLASH, *token))
		len = ft_strpchr(*token, SLASH);
	tmp2 = ft_strndup(&(*token)[ft_strpchr(*token, *(*token + 1)) + 1], len - 2);
	ft_strdel(token);
	*token = ft_strjoin(tmp1, tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (SUCCESS);
}

static int	ret_value(char **token)
{
	ft_strdel(token);
	*token = ft_itoa(g_retval);
	return (SUCCESS);
}

static int	positional_params(char **token)
{
	if (*(*token + 1) == STAR || *(*token + 1) == AROB)
	{
		if (view_pos_param(token) == SUCCESS)
			return (SUCCESS);
	}
	else if (*(*token + 1) == SHARP)
	{
		count_pos_params(token);
		return (SUCCESS);
	}
	else if (ft_isdigit(*(*token + 1)))
	{
		reach_pos_params(token);
		return (SUCCESS);
	}
	else if (*(*token + 1) == WHY)
	{
		ret_value(token);
		return (SUCCESS);
	}
	else if (*(*token + 1) == DASH)
	{
		ft_strdel(token);
		*token = ft_strdup("No options had been set");
		return (SUCCESS);
	}
	return (ERROR);
}

static int	special_params(char **token)
{
	if (script_param(token) == SUCCESS)
		return (SUCCESS);
	if (positional_params(token) == SUCCESS)
		return (SUCCESS);
	return (ERROR);
}

int						direct_exp(char **token)
{
	struct s_svar	*tmp;

	tmp = g_svar;
	if (special_params(token) == SUCCESS)
		return (SUCCESS);
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 1, ft_strlen(g_svar->key) - 1) == 0
				&& check_next_var(g_svar->key, token, 0) == SUCCESS)
		{
			ft_strdel(token);
			if (!(*token = ft_strdup(g_svar->value)))
				return (ERROR);
			g_svar = tmp;
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	if (!(*token = ft_strdup(EMPTY_STR)))
		return (ERROR);
	g_svar = tmp;
	return (SUCCESS);
}
