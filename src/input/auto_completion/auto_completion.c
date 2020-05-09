/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:12:14 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/09 23:45:17 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

void			print_double_char(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i] != NULL)
	{
		ft_putendl(tab[i]);
		i++;
	}
}

static int		pos_start(char *input, int start)
{
	int	i;
	int	new_w;
	int	tmp;

	i = 0;
	new_w = 1;
	tmp = 0;
	while (i < start)
	{
		if (input[i] == '\\')
		{
			if (new_w == 0)
			{
				tmp = i;
				new_w = 1;
			}
			i++;
		}
		else
		{
			if (ft_isspace(input[i]) || input[i] == '|' || input[i] == '&'
					|| input[i] == ';')
				new_w = 0;
			else if (new_w == 0)
			{
				tmp = i;
				new_w = 1;
			}
		}
		i++;
	}
	if (new_w == 1)
		start = tmp;
	return (start);
}

int				ft_restart(char *input, int start)
{
	start--;
	while (start >= 0 && !ft_isspace(input[start]) && !(input[start] == '|'
				|| input[start] == '&' || input[start] == ';'))
		start--;
	if (start != -1 && (input[start] == '|'
				|| input[start] == '&' || input[start] == ';'))
		return (1);
	while (start >= 0 && ft_isspace(input[start]))
		start--;
	if (start != -1 && (input[start] == '|'
				|| input[start] == '&' || input[start] == ';'))
		return (1);
	else
		return (0);
}

int				ft_auto_completion(t_tst *t, char *input, char ***w, int start)
{
	int		cursor;
	int		ret;
	char	tmp;

	cursor = start;
	start = pos_start(input, start);
	tmp = input[cursor];
	input[cursor] = '\0';
	if (input[start] == '$')
	{
		ret = 1;
		ft_putchar('\n');
		if (input[start + 1] == '{')
			ret = 2;
		if (ft_env_var(&input[start + ret], ret, w) == 0)
		{
			input[cursor] = tmp;
			return (0);
		}
	}
	else if (start == 0 || ft_restart(input, cursor))
	{
		if (((*w) = ft_binary(t, &input[start])) == NULL)
			if (((*w) = ft_path(&input[start])) == NULL)
			{
				input[cursor] = tmp;
				return (0);
			}
	}
	else
	{
		if (((*w) = ft_path(&input[start])) == NULL)
		{
			input[cursor] = tmp;
			return (0);
		}
	}
	if ((*w) && (*w)[0] != NULL && (*w)[1] == NULL)
	{
		input[cursor] = tmp;
		return (2);
	}
	input[cursor] = tmp;
	return (3);
}
