/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 13:50:19 by yberramd          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/05/18 14:18:43 by yberramd         ###   ########.fr       */
=======
/*   Updated: 2020/05/09 17:54:59 by tgouedar         ###   ########.fr       */
>>>>>>> e8b6a7cbec7d492934760c2cf7c72efe77d9c79a
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "shell_variables.h"

struct s_var	*g_svar;

static int	error_clean(int fd, char **get_line, char *home)
{
	ft_dprintf(2, "cannot allocate memory\n");
	ft_strdel(&home);
	close(fd);
	ft_strdel(get_line);
	return (0);
}

static int	init_clean(int fd, char **get_line, char *home)
{
	close(fd);
	ft_strdel(&home);
	ft_strdel(get_line);
	return (1);
}

int			assign_file_history(int fd, t_history *hist, int max, char *home)
{
	int		len;
	char	*get_line;

	len = 0;
	get_line = NULL;
	while (get_next_line(fd, &get_line) > 0 && len < max)
	{
		if (!(hist->str = ft_strdup(get_line)))
			return (error_clean(fd, &get_line, home));
		if (!(hist->next = (t_history*)malloc(sizeof(t_history))))
			return (error_clean(fd, &get_line, home));
		hist->next->previous = hist;
		hist = hist->next;
		ft_strdel(&get_line);
		len++;
	}
	if (hist->previous)
	{
		hist = hist->previous;
		free(hist->next);
		hist->next = NULL;
	}
	return (init_clean(fd, &get_line, home));
}

int			init_history(t_history *history)
{
	int		fd;
	int		max;
	char	*home;

	assign_max_home(&max, &home);
	if (home != NULL && home[0] != '\0' &&
			(fd = open(home, O_RDONLY | O_CREAT, 0600)) != -1)
		return (assign_file_history(fd, history, max, home));
	if (home == NULL || home[0] != '\0')
	{
		ft_dprintf(2, "history: can't open %s\n", home);
		ft_strdel(&home);
		return (0);
	}
	ft_strdel(&home);
	return (1);
}
