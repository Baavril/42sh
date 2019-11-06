/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2019/10/18 17:29:13 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/builtin_test.h"
#include "../../../../libft/include/libft.h"
#include "../../../../include/builtins.h"

/*int		ft_isin(char c, char *str)
{
	while (*str)
	{
		if (*str - c == e_success)
			return (e_success);
		str++;
	}
	return (e_failure);
}*/

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
		if (tmp_rets[i] == e_success)
		{
			free(tmp_rets);
			return (e_success);
		}
		++i;
	}
	free(tmp_rets);
	return (e_failure);
}
