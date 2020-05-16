/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:21:08 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/09 18:03:34 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

struct s_var	*g_svar;

int				delete_history(t_history *history)
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

static int		w_history(const char *line, int fd)
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

static int		mv_hist(t_history **history, int new_hist, int max)
{
	int	len;
	int	ret;

	len = 0;
	if (new_hist == 0)
	{
		while ((*history) && (*history)->next)
			(*history) = (*history)->next;
		while ((*history) && (*history)->previous && len++ < (max - 1))
			(*history) = (*history)->previous;
	}
	else if (new_hist == 1)
	{
		if ((ret = modif_hist(history, max)) <= 0)
			return (ret);
		while ((*history) && (*history)->next)
			(*history) = (*history)->next;
		while ((*history) && (*history)->previous && len++ < (max - 1))
			(*history) = (*history)->previous;
	}
	return (1);
}

static int		write_history(t_history *history, char *home, int max,
																int new_hist)
{
	int	fd;
	int	ret;

	if ((ret = mv_hist(&history, new_hist, max)) <= 0)
		return (ret);
	if ((fd = open(home, O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1)
		return (-1);
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

int				delete(t_history *history2, int flag)
{
	int					max;
	int					ret;
	char				*home;
	static t_history	*history = NULL;
	static int			new_hist = 0;

	if (history == NULL)
		history = history2;
	if (flag == NEW_HIST)
	{
		new_hist = 1;
		return (new_history(&history));
	}
	if (assign_max_home(&max, &home) == 0)
		return (0);
	if (home[0] != '\0')
	{
		if ((ret = write_history(history, home, max, new_hist)) == -1)
			ft_dprintf(2, "history: can't open %s\n", home);
		else if (ret == 0)
			ft_dprintf(2, "cannot allocate memory\n");
	}
	ft_strdel(&home);
	delete_history(history);
	return (1);
}
