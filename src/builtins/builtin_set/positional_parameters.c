/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positional_parameters.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:21:48 by bprunev           #+#    #+#             */
/*   Updated: 2020/03/08 16:01:20 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "shell_variables.h"
#include "libft.h"

extern struct s_svar	*g_svar;
extern struct s_pos		*g_pos;

static void				listpos_back(struct s_pos *new_back)
{
	struct s_pos	*voyager;

	if (!g_pos)
		return ;
	else
	{
		voyager = g_pos;
		while (voyager->next)
			voyager = voyager->next;
		voyager->next = new_back;
	}
}

static struct s_pos		*newnodpos(char *env, int exp)
{
	struct s_pos	*pos_lst;

	pos_lst = NULL;
	if (*env)
	{
		if (!(pos_lst = (struct s_pos*)malloc(sizeof(struct s_pos))))
			return (NULL);
		pos_lst->str = ft_strdup(env);
		pos_lst->key = ft_strdupto(env, '=');
		pos_lst->value = ft_strdupfm(env, '=');
		pos_lst->exp = exp;
		pos_lst->next = NULL;
	}
	return (pos_lst);
}

static void				setposvar(char *key, char *value)
{
	char	*set;

	set = ft_strjoin(key, value);
	listpos_back(newnodpos(set, 0));
	ft_strdel(&set);
}

static int				set_first_positional_param(char **tokens, int pos)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	if (tokens[1])
	{
		tmp1 = ft_itoa(pos);
		tmp2 = ft_strjoin(tmp1, "=");
		tmp3 = ft_strjoin(tmp2, tokens[1]);
		g_pos = newnodpos(tmp3, 0);
		ft_strdel(&tmp1);
		ft_strdel(&tmp2);
		ft_strdel(&tmp3);
	}
	return (SUCCESS);
}

int						set_positional_params(char **tokens)
{
	int				i;
	int				pos;
	char			*tmp1;
	char			*tmp2;
	struct s_pos	*ptr;

	i = 2;
	pos = 1;
	set_first_positional_param(tokens, pos);
	ptr = g_pos;
	++pos;
	while (tokens[i])
	{
		tmp1 = ft_itoa(pos);
		tmp2 = ft_strjoin(tmp1, "=");
		ft_strdel(&tmp1);
		setposvar(tmp2, tokens[i]);
		ft_strdel(&tmp2);
		g_pos = g_pos->next;
		++pos;
		++i;
	}
	g_pos = ptr;
	return (0);
}
