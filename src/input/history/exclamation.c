/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:59:00 by yberramd          #+#    #+#             */
/*   Updated: 2020/02/29 15:59:08 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

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

int			exclamation_point(char *line, t_history *history, char **cmd)
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
