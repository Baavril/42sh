/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_exclamation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 16:00:13 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/19 16:07:25 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "error.h"

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
		psherror(e_cannot_allocate_memory, NULL, e_invalid_type);
		ft_strdel(&cmd);
		return (0);
	}
	return (1);
}

static int	ft_simple_quote(char **line, int i, int b)
{
	if ((*line)[i] == '\'')
		b ^= 1;
	return (b);
}

int			s_exclamation(char **line, t_history *history, int *ret, char *cmd)
{
	int		i;
	int		b;
	int		q;

	b = 0;
	q = 0;
	i = 0;
	while ((*line)[i] != '\0')
	{
		b = brackets(line, i, b);
		q = ft_simple_quote(line, i, q);
		if ((*line)[i] == '!' && (*line)[i + 1] != '\0'
				&& !ft_isseparator(&(*line)[i + 1]) && b == 0 && q == 0)
		{
			if ((*ret = exclamation_point(&line[0][i], history, &cmd)) != -1)
			{
				if (!(add_exclamation_string(*ret, line, cmd, i)))
					return (0);
			}
			else
			{
				psherror(e_event_not_found, &(*line)[i], e_cmd_type);
				break ;
			}
		}
		if ((*line)[i] == '\\')
			i++;
		i++;
	}
	return (1);
}
