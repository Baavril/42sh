/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 13:50:19 by yberramd          #+#    #+#             */
/*   Updated: 2020/03/08 16:56:57 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static int	error_clean(int fd, char **get_line)
{
	ft_dprintf(2, "cannot allocate memory\n");
	close(fd);
	ft_strdel(get_line);
	return (0);
}

static int	init_clean(int fd, char **get_line)
{
	close(fd);
	ft_strdel(get_line);
	return (1);
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
			return (error_clean(fd, &get_line));
		if (!(history->next = (t_history*)malloc(sizeof(t_history))))
			return (error_clean(fd, &get_line));
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
	return (init_clean(fd, &get_line));
}

int			init_history(t_history *history, char **home)
{
	int		fd;

	if (!init_file_history(home))
		return (0);
	if ((fd = open(*home, O_RDONLY | O_CREAT, 0600)) != -1)
		return (assign_file_history(fd, history));
	ft_dprintf(2, "history: can't open %s\n", home);
	return (0);
}
