/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 13:53:47 by yberramd          #+#    #+#             */
/*   Updated: 2019/09/25 15:56:33 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "history.h"

static int	delete_history(t_history *history)
{
	t_history	*tmp;

	if (history->str)
		ft_strdel(&history->str);
	tmp = history->next;
	history = NULL;
	history = tmp;
	while (history)
	{
		if (history->str)
			ft_strdel(&history->str);
		tmp = history->next;
		free(history);
		history = NULL;
		history = tmp;
	}
	return (1);
}

static int	delete(t_history *history, char *home)
{
	ft_strdel(&home);
	delete_history(history);
	return (1);
}

static int	w_history(char *line, int fd)
{
	int	len;

	len = ft_strlen(line);
	if (write(fd, line, len) != len)
		return (-1);
	if (write(fd, "\n", 1) != 1)
		return (-1);
	return (1);
}

static int	add_history(char *line, t_history *history)
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

/*static int	ft_strcmp_n(const char *line, const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while ((line[i] == str[i]) && (line[i] || str[i] != '\0'))
		i++;
	if (line[i] == '\0' && str[i] == '\n')
		return (0);
	return (1);
}*/

static int	add_cmd(char *line, t_history *history, char *home)
{
	int	fd;

	fd = open(home, O_WRONLY | O_APPEND);
	if (fd != -1)
	{
		while (history->next)
			history = history->next;
		if ((history->str == NULL || ft_strcmp(line, history->str) != 0)
			 && ft_isspace(line[0]) != 1)
		{
			if (add_history(line, history) == -1)
			{
				close(fd);
				return (-1);
			}
			if (w_history(line, fd) == -1)
			{
				close(fd);
				return (-1);
			}
		}
		close(fd);
		return (1);
	}
	return (-1);
}

static int	ft_search(t_history *history, char *line, char **cmd)
{
	while (history->next)
		history = history->next;
	while (history->previous)
	{
		if (history->str != NULL && line != NULL && ft_strstr(history->str, line) != NULL)
		{
			*cmd = history->str;
			return (1);
		}
		history = history->previous;
	}
	return (-1);
}

static int	search_history(t_history *history, char *line, char **cmd)
{
	while (history->next)
		history = history->next;
	while (history->previous)
	{
		if (history->str != NULL && line != NULL && ft_strcmp(history->str, line) > 0)
		{
			*cmd = history->str;
			return (1);
		}
		history = history->previous;
	}
	return (-1);
}

static int init_clean(int fd, char *line)
{
	close(fd);
	ft_strdel(&line);
	return (-1);
}

static int	init_history(t_history *history, char **home)
{
	int		fd;
	char	*line;

	line = NULL;
	if (!(*home = ft_strjoin(getenv("HOME"), "/.42sh_history")))
		return (-1);
	if ((fd = open(*home, O_RDONLY | O_CREAT, 0600)) != -1)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (!(history->str = ft_strdup(line)))
				return (init_clean(fd, line));
			if (!(history->next = (t_history*)malloc(sizeof(t_history))))
				return (init_clean(fd, line));
			history->next->previous = history;
			history = history->next;
			ft_strdel(&line);
		}
		if (history->previous)
		{
			history = history->previous;
			free(history->next);
			history->next = NULL;
		}
		init_clean(fd, line);
		return (1);
	}
	return (-1);
}

int		history(int flag, char *line, char **cmd)
{
	static t_history	history = {NULL, NULL, NULL};
	static char			*home = NULL;

	if (flag == INIT)
		return (init_history(&history, &home));
	if (flag == DELETE)
		return (delete(&history, home));
	if (flag == ADD_CMD)
		return (add_cmd(line, &history, home));
	if (flag == SEARCH)
		return (ft_search(&history, line, cmd));
	if (flag == HISTORY_SEARCH)
		return (search_history(&history, line, cmd));
	return (-1);
}
