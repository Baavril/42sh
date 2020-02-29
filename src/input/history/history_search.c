/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 16:05:44 by yberramd          #+#    #+#             */
/*   Updated: 2020/02/29 16:05:53 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static int	ft_retinchr(char *str, char c)
{
	int i;

	i = 1;
	while (str[i - 1])
	{
		if (str[i - 1] - c == 0)
			return (i);
		i++;
	}
	return (1);
}

int			ft_search(t_history *history_2, const char *line, char **cmd, int f)
{
	static t_history *history = NULL;

	if (!history || f == RESET)
	{
		if (!history)
			history = history_2;
		while (history->next)
			history = history->next;
	}
	if (f != RESET)
	{
		history_2 = history;
		while (history_2->previous)
		{
			if (history_2->str != NULL && line != NULL && *line
					&& ft_strstr(history_2->str, line) != NULL)
			{
				history = history_2;
				*cmd = history->str;
				return (ft_retinchr(*cmd, line[0]));
			}
			history_2 = history_2->previous;
		}
	}
	return (f == RESET ? 1 : 0);
}

int			search_history(t_history *history, char *line, char **cmd)
{
	while (history->next)
		history = history->next;
	while (history->previous)
	{
		if (history->str != NULL && line != NULL
				&& ft_strfchr(history->str, line) != 0)
		{
			*cmd = history->str;
			return (1);
		}
		history = history->previous;
	}
	return (0);
}
