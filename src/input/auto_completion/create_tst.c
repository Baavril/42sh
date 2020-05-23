/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 15:18:57 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/23 15:35:24 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

int				search_tst(t_tst *tst, char *str)
{
	if (tst)
	{
		if ((*str) != '\0')
		{
			if ((*str) == tst->c)
				return (search_tst(tst->middle, (str + 1)));
			if ((*str) > tst->c)
				return (search_tst(tst->right, str));
			if ((*str) < tst->c)
				return (search_tst(tst->left, str));
		}
		if (tst->end == true)
			return (1);
	}
	return (0);
}

static int		last_char(t_tst **tst)
{
	t_tst	*cpy;

	cpy = NULL;
	if ((*tst)->middle)
		(*tst)->end = true;
	else
	{
		if (!(cpy = (t_tst*)malloc(sizeof(t_tst))))
			return (-1);
		(*tst)->middle = cpy;
		cpy->c = '\0';
		cpy->end = true;
		cpy->left = NULL;
		cpy->middle = NULL;
		cpy->right = NULL;
	}
	return (1);
}

static int		tst_end(int i, char *str, t_tst *tst)
{
	if (tst->c == '\0' && str[i] != '\0')
	{
		tst->c = str[i];
		i++;
	}
	if (str[i] != '\0')
		return (new_word(str, &tst->middle, i));
	if (tst->c != '\0')
		return (last_char(&tst));
	return (1);
}

static int		add_word(char *str, t_tst *tst)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && tst->c != '\0')
	{
		if (str[i] == tst->c)
		{
			tst = tst->middle;
			i++;
		}
		if (tst->c != '\0' && str[i] > tst->c && str[i] != '\0')
		{
			if (tst->right == NULL)
				return (new_word(str, &tst->right, i));
			tst = tst->right;
		}
		if (tst->c != '\0' && str[i] < tst->c && str[i] != '\0')
		{
			if (tst->left == NULL)
				return (new_word(str, &tst->left, i));
			tst = tst->left;
		}
	}
	return (tst_end(i, str, tst));
}

int				create_tst(char **binaires, t_tst **tst)
{
	int		i;

	i = 0;
	if (binaires && binaires[i] != NULL)
	{
		if (new_word(binaires[i], tst, 0) == -1)
			return (-1);
		i++;
	}
	while (binaires && binaires[i] != NULL)
	{
		if (add_word(binaires[i], *tst) == -1)
			return (-1);
		i++;
	}
	return (1);
}
