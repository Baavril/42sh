/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 13:50:19 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/21 18:00:02 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "error.h"
#include "shell_variables.h"

struct s_var	*g_svar;

static int	error_clean(int fd, char **get_line)
{
	psherror(e_cannot_allocate_memory, NULL, e_invalid_type);
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

int			assign_file_history(int fd, t_history *hist, int max)
{
	int		len;
	char	*get_line;

	len = 0;
	get_line = NULL;
	while (get_next_line(fd, &get_line) > 0 && len < max)
	{
		if (!(hist->str = ft_strdup(get_line)))
			return (error_clean(fd, &get_line));
		if (!(hist->next = (t_history*)malloc(sizeof(t_history))))
			return (error_clean(fd, &get_line));
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
	return (init_clean(fd, &get_line));
}

int			init_history(t_history *history, char **home)
{
	int		fd;
	int		max;

	if (assign_max_home(&max, home) == 0)
		return (0);
	if ((*home)[0] != '\0' && (fd = open((*home), O_RDONLY |
			O_CREAT, 0600)) != -1)
		return (assign_file_history(fd, history, max));
	if ((*home) == NULL || (*home)[0] != '\0')
	{
		psherror(e_permission_denied, (*home), e_cmd_type);
		return (0);
	}
	return (1);
}
