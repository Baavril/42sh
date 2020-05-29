/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_no_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 16:44:11 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/29 18:57:16 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"
#include "error.h"

extern int		g_arg;

static int		write_fc_file(char **option, int fd)
{
	int		max;
	char	*cmd;

	max = 1;
	history(FIRST, NULL, &cmd);
	while (history(FORWARD, NULL, &cmd) != 2 && cmd)
		max++;
	if (option[0] && option[1])
		ft_two_number_w(option, max, fd);
	else if (option[0])
	{
		if (ft_strisnbr(option[0]))
			ft_one_number_w(option[0], fd);
		else
			ft_dprintf(2, "42sh: fc: %s: numeric argument required\n",
																option[0]);
	}
	else
	{
		history(LAST, NULL, &cmd);
		history(BACKWARD, NULL, &cmd);
		ft_dprintf(fd, "%s\n", cmd);
	}
	return (0);
}

static int		malloc_option(char **argv, char **option)
{
	if (argv[1])
	{
		if (!(option[0] = ft_strdup(argv[1])))
			return (0);
		if (argv[2])
			if (!(option[1] = ft_strdup(argv[2])))
				return (0);
	}
	return (1);
}

int				ft_fc(char **option, char **argv)
{
	int	fd;

	if (!malloc_option(argv, option))
		return (0);
	if ((fd = open("/tmp/42sh-fc", O_TRUNC | O_CREAT | O_RDWR, 0600)) == -1)
	{
		psherror(e_permission_denied, "/tmp/42sh-fc", e_cmd_type);
		return (0);
	}
	write_fc_file(option, fd);
	close(fd);
	return (1);
}
