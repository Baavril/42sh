/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:21:48 by baavril           #+#    #+#             */
/*   Updated: 2020/01/19 12:59:15 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "shell_variables.h"
#include "libft.h"

extern struct s_svar	*g_svar;
extern struct s_pos		*g_pos;

void					prtlist()
{
	struct s_svar *voyager;

	voyager = g_svar;
	while (g_svar)
	{
		printf("%s\n", ((char*)g_svar->str));
		g_svar = g_svar->next;
	}
	g_svar = voyager;
}

void	listpos_back(struct s_pos *new_back)
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

struct s_pos	*newnodpos(char *env, int exp)
{
	struct s_pos *pos_lst;

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

void	setposvar(char *key, char *value)
{
	char	*set;

	set = ft_strjoin(key, value);
	listpos_back(newnodpos(set, 0));
	ft_strdel(&set);
}


static int				set_positional_parameters(char **tokens)
{
	int				i;
	int				pos;
	char			*tmp1;
	char			*tmp2;
	struct s_pos	*voyager;

	i = 2;
	pos = 0;
	g_pos = newnodpos(tokens[1], 0);
	voyager = g_pos;
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
	g_pos = voyager;
	while (g_pos)
	{
		printf("%s\n", ((char*)g_pos->str));
		g_pos = g_pos->next;
	}
	g_pos = voyager;
	return (0);
}

static void	free_pos_list(void)
{
	struct s_pos	*tmp1;

	while (g_pos)
	{
		tmp1 = g_pos->next;
		ft_strdel(&(g_pos->str));
		ft_strdel(&(g_pos->key));
		ft_strdel(&(g_pos->value));
		free(g_pos);
		g_pos = tmp1;
	}
}

int						cmd_set(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	if (argc == 1)
		prtlist();
	else
	{
		free_pos_list();
		set_positional_parameters(argv);
	}
	return (0);
}
