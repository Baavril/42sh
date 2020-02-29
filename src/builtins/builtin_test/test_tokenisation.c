/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_tokenisation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2019/11/09 11:44:32 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_test.h"

int		find_next_opt(char **argv, int flag, int init)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (((init == 0 && *argv[x] == '-'
	&& (int)ft_strlen(argv[x]) == 2)
	&& (argv[x][1] == 'a' || argv[x][1] == 'o')))
		x++;
	while (argv[x])
	{	
		if (((*argv[x] == '-' && (int)ft_strlen(argv[x]) == 2)
		&& (argv[x][1] == 'a' || argv[x][1] == 'o')))
		{
			if (x > 0 && (*(argv[x - 1]) - '-')  != E_SUCCESS)
			{
				(flag) ? y++: y;
				return (y);
			}
		}
		y++;
		x++;
	}
	return (y);
}

char	**split_btw_opts(char **argv, int opt)
{
	int		i;
	int		j;
	char	**args;

	i = 0;
	j = 0;
	if (!(args = (char **)malloc(sizeof(char*) * (opt + 1))))
		return (NULL);
	while (argv[i])
	{
		if ((argv[i][0] == '-' && (int)ft_strlen(argv[i]) == 2
		&& (argv[i][1] == 'a' || argv[i][1] == 'o'))
		&& ((i > 0 && (*(argv[i - 1]) - '-')  != E_SUCCESS)))
		{
			args[j] = 0;
			return (args);
		}
		if (!(args[j] = ft_strdup(argv[i])))
			return (NULL);
		i++;
		j++;
	}
	args[j] = 0;
	return (args);
}

int		ft_retnbr_opts(char **argv)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "-a") == E_SUCCESS
		|| ft_strcmp(argv[i], "-o") == E_SUCCESS)
		{
			if (i > 0 && (*(argv[i - 1]) - '-')  != E_SUCCESS)
				ret++;
		}
		i++;
	}
	return ((ret) ? ret : 0);
}

char	*ft_ret_optstring(char **argv, int exps)
{
	int i;
	int x;
	char *opts;

	i = 0;
	x = 0;
	opts = NULL;
	if (!(opts = (char*)malloc(sizeof(char) * (exps + 1))))
		return (NULL);
	while (argv[i])
	{
		if (argv[i][0] == '-' && (int)ft_strlen(argv[i]) == 2
		&& (argv[i][1] == 'a' || argv[i][1] == 'o'))
		{
			if (i > 0 && (*(argv[i - 1]) - '-')  != E_SUCCESS)
			{
				opts[x] = argv[i][1];
				x++;
			}
		}
		i++;
	}
	opts[x] = '\0';
	return (opts);
}
