/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:59:39 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/21 13:23:31 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "job.h"

static char **position_token(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && *(cmd[i]) == ';')
	{
		++i;
	}
	while (cmd[i] && *(cmd[i]) != ';')
	{
		++i;
	}
	while (cmd[i] && *(cmd[i]) == ';')
	{
		++i;
	}
	if (!(cmd[i]))
	{
		return (NULL);
	}
	return (&(cmd[i]));
}

static char **jump_sep(char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i] && *(cmd[i]) == ';')
	{
		++i;
	}
	return (&cmd[i]);
}

static char	**ft_sequence(char **cmd)
{
	char **seq;
	int	i;

	i = 0;
	while (cmd[i] && *(cmd[i]) != ';')
	{
		++i;
	}
	seq = (char**)ft_tabmalloc(i + 1);
	i = 0;
	while (cmd[i] && *(cmd[i]) != ';')
	{
		seq[i] = ft_strdup(cmd[i]);
		++i;
	}
	return (seq);
}

int	jcont(char **cmd, char **envp)
{
	char	**argv;
	int		ret;

	ret = 0;
	cmd = jump_sep(cmd);
	while (cmd && *cmd)
 	{
		argv = ft_sequence(cmd);
		if (**argv)
			ret = job(argv, envp);
		ft_tabdel(&argv);
		cmd = position_token(cmd);
	}
	return (ret);
}
