/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sequence.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:03:51 by abarthel          #+#    #+#             */
/*   Updated: 2019/11/13 12:03:53 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "pipelines.h"

char	**position_token(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && is_pipeline_separator(cmd[i]))
		++i;
	while (cmd[i] && !is_pipeline_separator(cmd[i]))
		++i;
	while (cmd[i] && is_pipeline_separator(cmd[i]))
		++i;
	if (!(cmd[i]))
		return (NULL);
	return (&(cmd[i]));
}

char **jump_sep(char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i] && is_pipeline_separator(cmd[i]))
		++i;
	return (&cmd[i]);
}

char				**get_sequence(char **cmd)
{
	char **seq;
	int	i;

	i = 0;
	while (cmd[i] && !is_pipeline_separator(cmd[i]))
		++i;
	seq = (char**)ft_tabmalloc(i + 1);
	i = 0;
	while (cmd[i] && !is_pipeline_separator(cmd[i]))
	{
		seq[i] = ft_strdup(cmd[i]);
		++i;
	}
	return (seq);
}