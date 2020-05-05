/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_exclamation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 16:00:13 by yberramd          #+#    #+#             */
/*   Updated: 2020/02/29 16:00:45 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static int	close_bracket(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ']')
			return (2);
		i++;
	}
	return (0);
}

static int	brackets(char **line, int i, int a)
{
	if ((*line)[i] == '[')
		a = close_bracket(&(*line)[i]);
	else if (a > 0 && (*line)[i] == '!')
		a -= 1;
	else if (a > 0 && (*line)[i] == ']')
		a = 0;
	return (a);
}

static int	add_exclamation_string(int ret, char **line, char *cmd, int i)
{
	if (!ret)
		return (0);
	(*line)[i] = '\0';
	if (!(*line = ft_strjoinfree(*line, cmd)))
	{
		ft_dprintf(2, "cannot allocate memory\n");
		ft_strdel(&cmd);
		return (0);
	}
	return (1);
}

int			s_exclamation(char **line, t_history *history, int *ret, char *cmd)
{
	int		i;
	int		a;

	a = 0;
	i = 0;
	while ((*line)[i] != '\0')
	{
		a = brackets(line, i, a);
		if ((*line)[i] == '!' && (*line)[i + 1] != '\0'
				&& !ft_isseparator(&(*line)[i + 1]) && a == 0)
		{
			if ((*ret = exclamation_point(&line[0][i], history, &cmd)) != -1)
			{
				if (!(add_exclamation_string(*ret, line, cmd, i)))
					return (0);
			}
			else
			{
				ft_dprintf(2, "42sh: %s: event not found\n", &(*line)[i]);
				break ;
			}
		}
		i++;
	}
	return (1);
}
