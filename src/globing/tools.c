/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_globing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/03/01 18:29:58 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"
#include "lexer.h"
#include "shell_variables.h"
#include "builtin_test.h"
#include "expansions.h"
#include "libft.h"

void		ft_freeintab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		ft_strdel(&tab[i++]);
}

void	ft_str_swap(char **a, char **b)
{
	char	*i;

	i = *a;
	*a = *b;
	*b = i;
}

int		sort_ascii_tab(char **tab)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = i + 1;
	len = ft_tablen(tab);
	while (i < (len - 1))
	{
		while (j < len)
		{
			if (ft_strspecasecmp(tab[i], tab[j]) > 0)
				ft_str_swap(&tab[i], &tab[j]);
			++j;
		}
		j = i + 1;
		++i;
	}
	return (SUCCESS);
}

int		ft_strspecasecmp(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	ret;

	i = 0;
	j = 0;
	ret = 0;
	while (s1[i] && s2[j])
	{
		if (!ft_isalnum(s1[i]) && ft_isprint(s1[i]))
				++i;
		if (!ft_isalnum(s2[j]) && ft_isprint(s1[i]))
				++j;
		if (ft_tolower(s1[i]) == ft_tolower(s2[j]) || s1[i] == s2[j])
		{
			++i;
			++j;
		}
		else
			break ;
	}
	ret = (unsigned char)ft_tolower(s1[i]) - (unsigned char)ft_tolower(s2[j]);
	return (ret = (ret == 0) ? ft_strlen(s2) - ft_strlen(s1) : ret);
}
