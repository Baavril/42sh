/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 13:53:47 by yberramd          #+#    #+#             */
/*   Updated: 2020/02/27 18:02:29 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "history.h"

extern struct s_svar	*g_svar;

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
	{
		close(fd);
		return (-1);
	}
	if (write(fd, "\n", 1) != 1)
	{
		close(fd);
		return (-1);
	}
	return (1);
}

static int	write_history(t_history *history, char *home)
{
	int len;
	int fd;

	len = 0;
	if ((fd = open(home, O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1)
		return (-1);
	while (history && history->next)
		history = history->next;
	while (history && history->previous && len++ < 499)
		history = history->previous;
	while (history && history->next)
	{
		if (w_history(history->str, fd) == -1)
			return (-1);
		history = history->next;
	}
	if (history && w_history(history->str, fd) == -1)
		return (-1);
	close(fd);
	return (1);
}

static int	delete(t_history *history, char *home)
{
	if (write_history(history, home) == -1)
		ft_dprintf(2, "history: can't open %s\n", home);
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

static int	add_cmd(const char *line, t_history *history)
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

static int	ft_search(t_history *history_2, const char *line, char **cmd, int f)
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

static int	search_history(t_history *history, char *line, char **cmd)
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

static int	error_clean(int fd, char *get_line)
{
	ft_dprintf(2, "cannot allocate memory\n");
	close(fd);
	ft_strdel(&get_line);
	return (0);
}

static int	init_clean(int fd, char *get_line)
{
	close(fd);
	ft_strdel(&get_line);
	return (1);
}

static int	ft_atoi_history(const char *str)
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

static int	init_file_history(char **home)
{
	char	*get_home;

	if ((get_home = getenv("HOME")))
	{
		if (!(*home = ft_strjoin(get_home, "/.42sh_history")))
		{
			ft_dprintf(2, "cannot allocate memory\n");
			return (0);
		}
	}
	else if (!(*home = ft_strdup("/tmp/.42sh_history")))
	{
		ft_dprintf(2, "cannot allocate memory\n");
		return (0);
	}
	return (1);
}

static int	assign_file_history(int fd, t_history *history)
{
	int		len;
	char	*get_line;

	len = 0;
	get_line = NULL;
	while (get_next_line(fd, &get_line) > 0 && len < 500)
	{
		if (!(history->str = ft_strdup(get_line)))
			return (error_clean(fd, get_line));
		if (!(history->next = (t_history*)malloc(sizeof(t_history))))
			return (error_clean(fd, get_line));
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
	return (init_clean(fd, get_line));
}

static int	init_history(t_history *history, char **home)
{
	int		fd;

	if (!init_file_history(home))
		return (0);
	if ((fd = open(*home, O_RDONLY | O_CREAT, 0600)) != -1)
		return (assign_file_history(fd, history));
	ft_dprintf(2, "history: can't open %s\n", home);
	return (0);
}

static int	exclamation_point_number(const char *line, t_history *h, char **c)
{
	int nbr;

	if ((nbr = ft_atoi_history(&line[1])) <= 0)
		return (-1);
	while (h->next && nbr > 1)
	{
		h = h->next;
		nbr--;
	}
	if (nbr > 1)
		return (-1);
	if (h)
		*c = h->str;
	return (2);
}

static int	exclamation_p_m_n(const char *line, t_history *h, char **cmd)
{
	int nbr;

	while (h->next)
		h = h->next;
	if ((nbr = ft_atoi_history(&line[2])) <= 0)
		return (-1);
	while (h->previous && nbr > 1)
	{
		h = h->previous;
		nbr--;
	}
	if (nbr > 1)
		return (-1);
	if (h)
		*cmd = h->str;
	return (2);
}

static int	exclamation_point_exclamation_point(t_history *history, char **cmd)
{
	while (history->next)
		history = history->next;
	if (history->str)
	{
		*cmd = history->str;
		return (2);
	}
	else
		return (-1);
}

static int	ft_isseparator(char *str)
{
	if (str[0] == '&' && str[1] == '&')
		return (1);
	else if (str[0] == '|' && str[1] == '|')
		return (1);
	else if (str[0] == '>' && str[1] == '>')
		return (1);
	else if (str[0] == '<' && str[1] == '<')
		return (1);
	else
		return (ft_isspace(str[0]) || str[0] == ';'
				|| str[0] == '<' || str[0] == '>');
}

static int	ft_str_exclamation_chr(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0' && !ft_isseparator(&str2[i]))
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str1[i] == '\0' && (str2[i] != '\0' || !ft_isseparator(&str2[i])))
		return (0);
	return (1);
}

static int	exclamation_s_history(t_history *history, char *line, char **cmd)
{
	if (history)
	{
		while (history->next)
			history = history->next;
		while (history->previous)
		{
			if (history->str != NULL && line != NULL
					&& ft_str_exclamation_chr(history->str, line) != 0)
			{
				*cmd = history->str;
				return (2);
			}
			history = history->previous;
		}
		if (history->str != NULL && line != NULL
				&& ft_str_exclamation_chr(history->str, line) != 0)
		{
			*cmd = history->str;
			return (2);
		}
	}
	return (-1);
}

static int	digit(char *line, t_history *history, char **cmd)
{
	int	i;
	int	ret;

	i = 1;
	if ((ret = exclamation_point_number(line, history, cmd)) != -1)
	{
		while (ft_isdigit(line[i]))
			i++;
		if (!(*cmd = ft_strjoin(*cmd, &line[i])))
			return (0);
	}
	return (ret);
}

static int	minus_digit(char *line, t_history *history, char **cmd)
{
	int	i;
	int	ret;

	i = 2;
	if ((ret = exclamation_p_m_n(line, history, cmd)) != -1)
	{
		while (ft_isdigit(line[i]))
			i++;
		if (!(*cmd = ft_strjoin(*cmd, &line[i])))
			return (0);
	}
	return (ret);
}

static int	exclamation_alone(char *line, t_history *history, char **cmd)
{
	int		i;
	int		ret;

	i = 1;
	if ((ret = exclamation_s_history(history, &line[1], cmd)) != -1)
	{
		while (line[i] != '\0' && !ft_isseparator(&line[i]))
			i++;
		if (!(*cmd = ft_strjoin(*cmd, &line[i])))
			return (0);
	}
	return (ret);
}

static int	exclamation_point(char *line, t_history *history, char **cmd)
{
	int		ret;

	ret = 1;
	if (ft_isdigit(line[1]))
	{
		if (!(ret = digit(line, history, cmd)))
			return (0);
	}
	else if (line[1] == '-' && ft_isdigit(line[2]))
	{
		if (!(ret = minus_digit(line, history, cmd)))
			return (0);
	}
	else if (line[1] == '!')
	{
		if ((ret = exclamation_point_exclamation_point(history, cmd)) != -1)
			if (!(*cmd = ft_strjoin(*cmd, &line[2])))
				return (0);
	}
	else if (line[1] != '\0' && !ft_isseparator(&line[1]))
	{
		if (!(ret = exclamation_alone(line, history, cmd)))
			return (0);
	}
	return (ret);
}

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
		ft_printf("str [%s]\n", *line);
		ft_strdel(&cmd);
		return (0);
	}
	return (1);
}

static int	s_exclamation(char **line, t_history *history, int *ret, char *cmd)
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

static int	history_cmd(char **line, t_history *history)
{
	int		ret;
	char	*cmd;

	ret = 1;
	cmd = NULL;
	if (!(s_exclamation(line, history, &ret, cmd)))
		return (0);
	if (ret == 2 && *line)
		ft_printf("%s\n", *line);
	if (ret != -1)
		add_cmd(*line, history);
	return (ret);
}

static int	get_first(t_history **history, char **cmd)
{
	while ((*history)->previous)
		(*history) = (*history)->previous;
	*cmd = (*history)->str;
	return (1);
}

static int	get_last(t_history **history, char **cmd)
{
	while ((*history)->next)
		(*history) = (*history)->next;
	*cmd = (*history)->str;
	return (1);
}

static int	get_next(t_history **history, char **cmd)
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

static int	get_previous(t_history **history, char **cmd)
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

static int	ft_swap_2(t_history **history, char *cmd)
{
	ft_strdel(&(*history)->str);
	if (!((*history)->str = ft_strdup(cmd)))
		return (-1);
	return (1);
}

static int	history_move(t_history *history_2, char **cmd, int flag)
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
	static char			*home = NULL;

	if (flag == BACKWARD || flag == FORWARD || flag == GET
			|| flag == FIRST || flag == LAST || flag == SWAP)
		return (history_move(&history, cmd, flag));
	if (flag == INIT)
		return (init_history(&history, &home));
	if (flag == DELETE)
		return (delete(&history, home));
	if (flag == ADD_CMD)
		return (history_cmd(line, &history));
	if (flag == SEARCH || flag == RESET)
		return (ft_search(&history, *line, cmd, flag));
	if (flag == HISTORY_SEARCH)
		return (search_history(&history, *line, cmd));
	return (0);
}
