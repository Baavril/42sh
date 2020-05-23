/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 14:30:54 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/23 14:44:10 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"
#include "error.h"

static char		*ft_strdup_bslash(char *input, int length)
{
	char	*tmp;
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (!(tmp = (char*)malloc(sizeof(char) * (length + 1))))
		return (NULL);
	while (input[i] != '\0')
	{
		if (input[i] == '\\')
			i++;
		tmp[y] = input[i];
		i++;
		y++;
	}
	tmp[y] = '\0';
	return (tmp);
}

static void		ft_assign_lb(char *input, int *i, int *length, char **last_b)
{
	(void)last_b;
	while (input[(*i)] != '\0' && !ft_isspace(input[(*i)]))
	{
		if (input[(*i)] == '/')
			(*last_b) = &input[(*i)];
		if (input[(*i)] == '\\')
		{
			(*i)++;
			(*length)--;
		}
		(*i)++;
	}
}

static char		*ft_dirchr(char *input)
{
	char	*cur_dir;
	char	*last_bslash;
	int		i;
	int		length;

	i = 0;
	length = 0;
	last_bslash = NULL;
	ft_assign_lb(input, &i, &length, &last_bslash);
	if (last_bslash != NULL)
	{
		*last_bslash = '\0';
		if (input[0] == '\0')
			cur_dir = ft_strdup("/");
		else
			cur_dir = ft_strdup_bslash(input, i + length);
		*last_bslash = '/';
	}
	else
		cur_dir = ft_strdup(getenv("PWD"));
	return (cur_dir);
}

DIR				*ft_assign_char(char *input, char **words)
{
	char	*point;
	DIR		*dir;

	point = ft_dirchr(input);
	if ((dir = opendir(point)) == NULL)
	{
		del_double_char(words);
		ft_strdel(&point);
		psherror(e_no_such_file_or_directory, NULL, e_invalid_type);
		return (NULL);
	}
	ft_strdel(&point);
	ft_putchar('\n');
	return (dir);
}
