/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 15:34:47 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/23 15:35:23 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

static t_tst	*first_cpy(char *str, t_tst **tst, int i)
{
	t_tst	*cpy;

	if (!(cpy = (t_tst*)malloc(sizeof(t_tst))))
		return (NULL);
	(*tst) = cpy;
	cpy->left = NULL;
	cpy->right = NULL;
	cpy->middle = NULL;
	cpy->c = str[i];
	cpy->end = false;
	return (cpy);
}

static int		assign_cpy(char *str, t_tst **cpy, int i)
{
	if (!((*cpy)->middle = (t_tst*)malloc(sizeof(t_tst))))
		return (-1);
	(*cpy) = (*cpy)->middle;
	(*cpy)->left = NULL;
	(*cpy)->right = NULL;
	(*cpy)->middle = NULL;
	(*cpy)->c = str[i];
	(*cpy)->end = false;
	return (1);
}

int				new_word(char *str, t_tst **tst, int i)
{
	t_tst	*cpy;

	if (str[i] != '\0')
	{
		if (!(cpy = first_cpy(str, tst, i)))
			return (-1);
		i++;
	}
	while (str[i] != '\0')
	{
		if (assign_cpy(str, &cpy, i++) == -1)
			return (-1);
	}
	if (i != 0)
	{
		if (!(cpy->middle = (t_tst*)malloc(sizeof(t_tst))))
			return (-1);
		cpy = cpy->middle;
		cpy->c = '\0';
		cpy->end = true;
		cpy->left = NULL;
		cpy->right = NULL;
		cpy->middle = NULL;
	}
	return (1);
}
