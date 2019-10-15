/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 13:53:47 by yberramd          #+#    #+#             */
/*   Updated: 2019/10/08 16:55:03 by yberramd         ###   ########.fr       */
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

static int	w_history(const char *line, int fd)
{
	int	len;

	len = ft_strlen(line);
	if (write(fd, line, len) != len)
		return (-1);
	if (write(fd, "\n", 1) != 1)
		return (-1);
	return (1);
}

static int 	write_history(t_history *history, char *home)
{
	int fd;

	if ((fd = open(home, O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1)
		return (-1);
	while (history && history->next)
	{
		if (w_history(history->str, fd) == -1)
		{
			close(fd);
			return (-1);
		}
		history = history->next;
	}
	if (w_history(history->str, fd) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (1);
}

static int	delete(t_history *history, char *home)
{
	write_history(history, home);
	ft_strdel(&home);
	delete_history(history);
	return (1);
}

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


static int	add_history_max_length(const char *line, t_history *history)
{
	while (history->previous)
		history = history->previous;
	ft_strdel(&history->str);
	while (history->next)
	{
		history->str = history->next->str;
		history = history->next;
	}
	if (!(history->str = ft_strdup(line)))
		return (-1);
	return (1);
}

static int	add_cmd(const char *line, t_history *history)//LIMIT 500
{
	int len;

	len = 0;//LIMIT
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
			if (len < 499)
			{
				if (add_history(line, history) == -1)
					return (-1);
			}
			else if (add_history_max_length(line, history) == -1)
				return (-1);
		}
		while (history->previous)
			history = history->previous;
		return (1);
	}
	return (-1);
}

static int	ft_search(t_history *history, const char *line, char **cmd)
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

static int	search_history(t_history *history, const char *line, char **cmd)
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

static int init_clean(int fd, char *get_line)
{
	close(fd);
	ft_strdel(&get_line);
	return (-1);
}

static int	init_history(t_history *history, char **home)
{
	int 	len;
	int		fd;
	char	*get_line;

	len = 0;
	get_line = NULL;
	if (!(*home = ft_strjoin(getenv("HOME"), "/.42sh_history")))
		return (-1);
	if ((fd = open(*home, O_RDONLY | O_CREAT, 0600)) != -1)
	{
		while (get_next_line(fd, &get_line) > 0 && len < 499)
		{
			if (!(history->str = ft_strdup(get_line)))
				return (init_clean(fd, get_line));
			if (!(history->next = (t_history*)malloc(sizeof(t_history))))
				return (init_clean(fd, get_line));
			history->next->previous = history;
			history = history->next;
			ft_strdel(&get_line);
			len++;
		}
		if (history->previous)
		{
			history = history->previous;
			free(history->next);
			history->next = NULL;
		}
		init_clean(fd, get_line);
		return (1);
	}
	return (-1);
}

static int		ft_atoi_history(const char *str)
{
	int				i;
	unsigned long	nbr;
	unsigned short	val;

	i = 0;
	nbr = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		++i;
	while (str[i] > 47 && str[i] < 58)
	{
		val = str[i] ^ ((1 << 5) | (1 << 4));
		nbr = nbr * 10 + val;
		if (nbr > 500)
			return (0);
		++i;
	}
	return (nbr);
}

static int		exclamation_point_number(const char *line, t_history *history, char **cmd)
{
	int nbr;

	if ((nbr = ft_atoi_history(&line[1])) <= 0)
		return (0);
	while (history->next && nbr > 1)
	{
		history = history->next;
		nbr--;
	}
	if (nbr > 1)
		return (0);
	if (history)
		*cmd = history->str;
	return (1);
}

static int		exclamation_point_minus_number(const char *line, t_history *history, char **cmd)
{
	int nbr;

	while (history->next)
		history = history->next;
	if ((nbr = ft_atoi_history(&line[2])) <= 0)
		return (0);
	while (history->previous && nbr > 1)
	{
		history = history->previous;
		nbr--;
	}
	if (nbr > 1)
		return (0);
	if (history)
		*cmd = history->str;
	return (1);
}

static int		exclamation_point_exclamation_point(t_history *history, char **cmd)
{
	while (history->next)
		history = history->next;
	if (history)
		*cmd = history->str;
	return (1);
}

static int		exclamation_point(const char *line, t_history *history, char **cmd)
{
	int ret;

	ret = 1;
	if (ft_isdigit(line[1]))
		ret = exclamation_point_number(line, history, cmd);
	else if (line[1] == '-' && ft_isdigit(line[2]))
		ret = exclamation_point_minus_number(line, history, cmd);
	else if (line[1] == '!')
		ret = exclamation_point_exclamation_point(history, cmd);
	else if (line[1] != '\0')
		ret = search_history(history, &line[1], cmd);//erreur cmd pas initialise
	else if (line[1] == '\0')
		*cmd = "!";
	if (ret > 0)
		add_cmd(*cmd, history);//A VOIR C'eST MOCHE
	return ((line[1] == '\0') ? 0 : ret);
}

static int 	get_first(t_history **history, char **cmd)
{
	while ((*history)->previous)
		(*history) = (*history)->previous;
	*cmd = (*history)->str;
	return (1);
}

static int 	get_last(t_history **history, char **cmd)
{
	while ((*history)->next)
		(*history) = (*history)->next;
	*cmd = (*history)->str;
	return (1);
}

static int 	get_next(t_history **history, char **cmd)
{
	if ((*history)->next)
	{
		(*history) = (*history)->next;
		*cmd = (*history)->str;
		return (1);
	}
	else
	{
		*cmd = (*history)->str;
		return (2);
	}
}

static int 	get_previous(t_history **history, char **cmd)
{
	if ((*history)->previous)
	{
		(*history) = (*history)->previous;
		*cmd = (*history)->str;
		return (1);
	}
	else
	{
		*cmd = (*history)->str;
		return (2);
	}
}

static int 	history_move(t_history *history_2, char **cmd, int flag)//suppression historique ou du pointeur en question
{
	static t_history *history = NULL;

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
		return (1);
	}
	else
		*cmd = NULL;
	return (0);
}

int		history(int flag, const char *line, char **cmd)//LIMITER HISTORY POUR LE RENDRE POSIX
{
	static t_history	history = {NULL, NULL, NULL};
	static char			*home = NULL;

	if (flag == BACKWARD || flag == FORWARD || flag == GET || flag == FIRST || flag == LAST)
		return (history_move(&history, cmd, flag));
	if (flag == EXCLAMATION && line[0] == '!')
		return (exclamation_point(line, &history, cmd));//ajout de ADD_CMD
	if (flag == INIT)
		return (init_history(&history, &home));
	if (flag == DELETE)
		return (delete(&history, home));
	if (flag == ADD_CMD)
		return (add_cmd(line, &history));
	if (flag == SEARCH)
		return (ft_search(&history, line, cmd));//from anywhere
	if (flag == HISTORY_SEARCH)
		return (search_history(&history, line, cmd));//debut fin
	return (-1);
}