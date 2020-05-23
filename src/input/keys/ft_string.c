/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 17:36:51 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/23 17:55:47 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "auto_completion.h"
#include "input.h"
#include "keys.h"

static void	ft_assign_tmp1(int start, int *i, char *input, char **tmp)
{
	*i = 0;
	while (*i < start)
	{
		(*tmp)[*i] = input[*i];
		(*i)++;
	}
}

static char	*ft_assign_tmp2(int start, int i, char *input, char **tmp)
{
	while (input[start] != '\0')
	{
		(*tmp)[i] = input[start];
		start++;
		i++;
	}
	(*tmp)[i] = '\0';
	return ((*tmp));
}

char		*ft_add_string(char *input, char **binary, int start)
{
	char	*tmp;
	int		len;
	int		i;
	int		y;

	i = 0;
	start = pos_start2(input, start);
	y = start;
	while (input[y] != '\0' && input[y] == (*binary)[i++])
		y++;
	if (input[y] != '\0')
		i--;
	len = ft_strlen((*binary)) - i;
	if (!(tmp = (char*)malloc(sizeof(char) * (len + ft_strlen(input) + 1))))
		return (NULL);
	len = i;
	ft_assign_tmp1(start, &i, input, &tmp);
	y = 0;
	while ((*binary)[y] != '\0')
	{
		tmp[i] = (*binary)[y];
		i++;
		y++;
	}
	return (ft_assign_tmp2(start + len, i, input, &tmp));
}

int			ft_string(char **buff, char **binary, t_tst *tst,
							t_cursor *cursor)
{
	char	*input;

	input = NULL;
	if (!(input = ft_add_string(*buff, &binary[0], cursor->start)))
	{
		del_tst(tst);
		del_double_char(binary);
		return (0);
	}
	set_string(buff, cursor, input);
	ft_strdel(&input);
	return (1);
}
