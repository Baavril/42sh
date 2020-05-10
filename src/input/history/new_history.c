/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 21:13:34 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/09 18:44:18 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

struct s_var	*g_svar;

int			new_history(t_history **history)
{
	if (history != NULL && (*history) != NULL)
	{
		while ((*history)->next != NULL)
			(*history) = (*history)->next;
	}
	return (1);
}

int			assign_max_home(int *max, char **home)
{
	char	*nbr;

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
	return (1);
}

static int	clean_home_histo(char *home, t_history *history)
{
	free(home);
	free(history);
	return (-1);
}

static void	assign_hist(t_history **history, t_history *new_history)
{
	t_history	*tmp;

	tmp = (*history)->previous;
	if (tmp)
	{
		(*history)->previous = NULL;
		tmp->next = NULL;
		while (tmp->previous)
			tmp = tmp->previous;
		delete_history(tmp);
	}
	if (new_history->str == NULL)
		free(new_history);
	else
	{
		while (new_history->next)
			new_history = new_history->next;
		new_history->next = (*history);
		(*history)->previous = new_history;
	}
}

int			modif_hist(t_history **history, int max)
{
	t_history	*new_history;
	char		*home;
	int			fd;

	if (!(new_history = (t_history*)malloc(sizeof(t_history))))
		return (0);
	new_history->previous = NULL;
	new_history->next = NULL;
	new_history->str = NULL;
	if (!(home = getshvar(HISTFILE)))
		return (0);
	if (home[0] != '\0')
	{
		if ((fd = open(home, O_RDONLY | O_CREAT, 0600)) == -1)
			return (clean_home_histo(home, new_history));
		if (assign_file_history(fd, new_history, max, home) == 0)
		{
			ft_strdel(&home);
			return (0);
		}
		assign_hist(history, new_history);
	}
	return (1);
}
