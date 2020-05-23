/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_comp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 17:47:22 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/23 17:53:36 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "auto_completion.h"
#include "input.h"
#include "keys.h"

static void	assign_tmp(char *tmp, char *binary, char *input, int y)
{
	int i;

	i = 0;
	while (input[i] == binary[i])
	{
		tmp[i] = binary[i];
		i++;
	}
	while (i < y)
	{
		tmp[i] = binary[i];
		i++;
	}
	tmp[i] = '\0';
}

static int	ft_strlen_modif(char *str)
{
	int i;

	i = 0;
	while (str && str[i] != '\0' && !ft_isspace(str[i]) && str[i] != '/'
			&& str[i] != '|' && str[i] != '&' && str[i] != ';')
		i++;
	return (i);
}

static int	cmp_binary(char *str1, char *str2, int y, char *input)
{
	int i;
	int tmp_y;

	tmp_y = y;
	i = 0;
	y = 0;
	while (str1[i] != '\0' && input[i] != '\0' && str1[i] == input[i])
		i++;
	while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i])
	{
		i++;
		y++;
	}
	if (tmp_y != -1)
		return ((tmp_y < y) ? tmp_y : y);
	else
		return (y);
}

int			dynamic_comp(char **binary, char *input, char **equal, int start)
{
	int		i;
	int		y;
	int		tmp_start;
	char	*tmp;

	tmp_start = pos_start2(input, start);
	y = -1;
	i = 1;
	tmp = binary[0];
	while (binary[i] != NULL && y != 0 && binary[0])
	{
		y = cmp_binary(binary[i], tmp, y, &input[tmp_start]);
		tmp = binary[i];
		i++;
	}
	if (y == 0 || y == -1)
		return (2);
	y += ft_strlen_modif(&input[tmp_start]);
	if (!(tmp = (char*)malloc(sizeof(char) * (y + 1))))
		return (0);
	assign_tmp(tmp, binary[0], &input[tmp_start], y);
	y =
		((*equal) = ft_add_string(input, &tmp, start)) ? 1 : 0;
	ft_strdel(&tmp);
	return (y);
}
