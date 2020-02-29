/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 15:34:57 by yberramd          #+#    #+#             */
/*   Updated: 2020/02/29 16:03:15 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int			ft_isseparator(char *str)
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

int			exclamation_s_history(t_history *history, char *line, char **cmd)
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

int			exclamation_p_m_n(const char *line, t_history *h, char **cmd)
{
	int nbr;

	while (h->next)
		h = h->next;
	if ((nbr = ft_atoi_history2(&line[2])) <= 0)
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

int			exclamation_point_number(const char *line, t_history *h, char **c)
{
	int nbr;

	if ((nbr = ft_atoi_history2(&line[1])) <= 0)
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
