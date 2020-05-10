/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 13:53:47 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/10 17:05:03 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "history.h"

static int	add_history(const char *line, t_history *history)
{
	if (history->str)
	{
		if (!(history->next = (t_history*)malloc(sizeof(t_history))))
			return (-1);
		history->next->previous = history;
		history = history->next;
		history->next = NULL;
		if (!(history->str = ft_strdup(line)))
			return (-1);
	}
	else if (!(history->str = ft_strdup(line)))
	{
		history->next = NULL;
		return (-1);
	}
	return (1);
}

static int	add_cmd(char *line, t_history *history)
{
	int len;

	len = 0;
	if (line != NULL)
	{
		while (history->next)
		{
			history = history->next;
			len++;
		}
		if ((history->str == NULL || ft_strcmp(line, history->str) != 0)
				&& ft_isspace(line[0]) != 1 && line[0] != '\0')
		{
			if (add_history(line, history) == -1)
			{
				ft_dprintf(2, "cannot allocate memory\n");
				return (0);
			}
		}
		return (1);
	}
	return (0);
}

static int	init_exclamation(char **line, t_history *history)
{
	int		ret;
	char	*cmd;

	ret = 1;
	cmd = NULL;
	if (!(s_exclamation(line, history, &ret, cmd)))
		return (0);
	if (ret == 2 && *line)
		ft_printf("%s\n", *line);
	return (ret);
}

static int	history_move(t_history *history_2, char **cmd, int flag)
{
	static t_history *history = NULL;

	if (cmd == NULL)
		return (0);
	if (!history)
		history = history_2;
	if (history)
	{
		if (flag == BACKWARD)
			return (get_previous(&history, cmd));
		if (flag == FORWARD)
			return (get_next(&history, cmd));
		if (flag == GET)
			*cmd = history->str;
		if (flag == FIRST)
			return (get_first(&history, cmd));
		if (flag == LAST)
			return (get_last(&history, cmd));
		if (flag == SWAP)
			return (ft_swap_2(&history, *cmd));
		return (1);
	}
	else
		*cmd = NULL;
	return (0);
}

int			history(int flag, char **line, char **cmd)
{
	static t_history	history = {NULL, NULL, NULL};

	if (flag == BACKWARD || flag == FORWARD || flag == GET
			|| flag == FIRST || flag == LAST || flag == SWAP)
		return (history_move(&history, cmd, flag));
	if (flag == INIT)
		return (init_history(&history));
	if (flag == DELETE || flag == NEW_HIST)
		return (delete(&history, flag));
	if (flag == ADD_CMD)
		return (add_cmd(*line, &history));
	if (flag == SEARCH || flag == RESET)
		return (ft_search(&history, *line, cmd, flag));
	if (flag == HISTORY_SEARCH)
		return (search_history(&history, *line, cmd));
	if (flag == EXCLAMATION)
		return (init_exclamation(line, &history));
	return (0);
}
