/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2019/11/09 11:46:36 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_test.h"

int		ft_strnlen(char c, char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] - c == 0)
			ret++;
		i++;
	}
	return (ret);
}

int		ft_delalloc(char **argv, int ret)
{
	int	j;
	int	k;

	k = ret;
	ret *= 2;
	j = ft_tablen(argv);
	while (ret)
	{
		ft_strdel(&argv[j - ret]);
		ret--;
	}
	return (k);
}

int		ft_tabret(char *opts, int *tmp_rets)
{
	int	i;
	int	nb;

	i = 0;
	nb = ft_strnlen('o', opts);
	while (i <= nb)
	{
		if (tmp_rets[i] == E_SUCCESS)
		{
			free(tmp_rets);
			return (E_SUCCESS);
		}
		++i;
	}
	free(tmp_rets);
	return (E_FAILURE);
}
