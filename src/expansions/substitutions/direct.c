/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_substitution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/03/08 13:35:40 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"
#include "builtins.h"
#include "libft.h"
#include "expansions.h"
#include "shell_variables.h"

extern struct s_svar	*g_svar;
extern struct s_pos		*g_pos;
extern char				*g_bgpid;
extern int				g_retval;

char				*get_var_value(char *var_name)
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

static int			script_param(char **token)
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
		else if (ft_strlchr(*token, '"'))
			len = ft_strlchr(*token, '"');
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

static int			view_pos_param(char **token)
{
	char			*tmp2;
	char			*tmp3;
	char			*tmp4;
	struct s_pos	*ptr;
	int				len;
	char			*esc;

	tmp2 = NULL;
	tmp3 = NULL;
	tmp4 = NULL;
	esc = " ";
	len = ft_strlen(*token);
	if (*(*token + 1) == STAR && token[0][len - 1] == '"')
	{
		if (!(esc = get_var_value("IFS=")))
			esc = ft_strdup(" ");
	}
	if (!g_pos)
		return (ERROR);
	ptr = g_pos;
	while (ptr->next)
	{
		tmp3 = (tmp2) ? tmp2 : ft_strjoin(ptr->value, esc);
		tmp2 = ft_strjoin(tmp3, ptr->next->value);
		tmp4 = tmp2;
		tmp2 = ft_strjoin(tmp4, esc);
		ptr = ptr->next;
		ft_strdel(&tmp3);
		ft_strdel(&tmp4);
	}
	if (tmp2)
	{
		if (ft_isin(SLASH, *token))
			len = ft_strpchr(*token, SLASH);
		else if (ft_strlchr(*token, '"'))
			len = ft_strlchr(*token, '"');
		tmp4 = ft_strndup(&(*token)[ft_strpchr(*token, STAR) + 1], len - 2);
		ft_strdel(token);
		if (!ft_isspace(esc[0]))
		{
			tmp3 = ft_strndup(tmp2, ft_strlen(tmp2) - 1);
			ft_strdel(&tmp2);
			tmp2 = tmp3;
		}
		*token = ft_strjoin(tmp2, tmp4);
		ft_strdel(&tmp2);
	}
	ft_strdel(&esc);
	return (SUCCESS);
}

static int			count_pos_params(char **token)
{
	int				i;
	struct s_pos	*ptr;

	i = 0;
	ptr = g_pos;
	while (ptr)
	{
		++i;
		ptr = ptr->next;
	}
	ft_strdel(token);
	*token = ft_itoa(i);
	return (SUCCESS);
}

static int			reach_pos_params(char **token)
{
	char			*tmp1;
	char			*tmp2;
	int				len;
	struct s_pos	*ptr;

	tmp2 = NULL;
	len = ft_strlen(*token);
	ptr = g_pos;
	while (ptr)
	{
		if (ft_strncmp(ptr->key, *token + 1, 1) == 0)
			break ;
		ptr = ptr->next;
	}
	tmp1 = (ptr) ? ptr->value : NULL;
	if (ft_isin(SLASH, *token))
		len = ft_strpchr(*token, SLASH);
	else if (ft_strlchr(*token, '"'))
		len = ft_strlchr(*token, '"');
	tmp2 = ft_strndup(&(*token)[ft_strpchr(*token, *(*token + 1))
			+ 1], len - 2);
	ft_strdel(token);
	*token = ft_strjoin(tmp1, tmp2);
	ft_strdel(&tmp2);
	return (SUCCESS);
}

static int			ret_value(char **token)
{
	ft_strdel(token);
	*token = ft_itoa(g_retval);
	return (SUCCESS);
}

static int			positional_params2(char **token)
{
	if (*(*token + 1) == DASH)
	{
		ft_strdel(token);
		*token = ft_strdup(EMPTY_STR);
		return (SUCCESS);
	}
	else if (*(*token + 1) == DOLLAR)
	{
		ft_strdel(token);
		*token = get_var_value("PID");
		return (SUCCESS);
	}
	else if (*(*token + 1) == EXCLAM)
	{
		ft_strdel(token);
		if (!(*token = ft_strdup((g_bgpid) ? g_bgpid : EMPTY_STR)))
			return (0);
		return (SUCCESS);
	}
	return (ERROR);
}

static int			positional_params(char **token)
{
	int		ret;

	ret = ERROR;
	if (*(*token + 1) == STAR || *(*token + 1) == AROB)
		ret = view_pos_param(token);
	else if (*(*token + 1) == SHARP)
		ret = count_pos_params(token);
	else if (ft_isdigit(*(*token + 1)))
		ret = reach_pos_params(token);
	else if (*(*token + 1) == WHY)
		ret = ret_value(token);
	else
		ret = positional_params2(token);
	return (ret);
}

static int			special_params(char **token)
{
	if (script_param(token) == SUCCESS)
		return (SUCCESS);
	if (positional_params(token) == SUCCESS)
		return (SUCCESS);
	return (ERROR);
}

int					direct_exp(char **token)
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
