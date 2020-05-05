/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 13:50:19 by yberramd          #+#    #+#             */
/*   Updated: 2020/03/08 19:30:07 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "shell_variables.h"

struct s_var	*g_svar;

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

static int	assign_file_history(int fd, t_history *history, int max)
{
	int		len;
	char		*get_line;

	len = 0;
	get_line = NULL;
	while (get_next_line(fd, &get_line) > 0 && len < max)
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

int			init_history(t_history *history, char **home, int *max)
{
	int		fd;
	char		*nbr;

	if (!(nbr = getshvar(HISTSIZE)))
	{
		ft_dprintf(2, "cannot allocate memory\n");
		return (0);
	}
	*max = ft_atoi(nbr);
	ft_strdel(&nbr);
	if (!(*home = getshvar(HISTFILE)))
	{
		ft_dprintf(2, "cannot allocate memory\n");
		return (0);
	}
	if (*home[0] != '\0' && (fd = open(*home, O_RDONLY | O_CREAT, 0600)) != -1)
		return (assign_file_history(fd, history, *max));
	if (*home == NULL || *home[0] != '\0')
	{
		ft_dprintf(2, "history: can't open %s\n", *home);
		return (0);
	}
	return (1);
}
