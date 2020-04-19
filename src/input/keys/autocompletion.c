/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:31:43 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/08 17:51:39 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "auto_completion.h"
#include "input.h"
#include "keys.h"

/*
** plus de leaks sur les tab keys -> fonctions a
** realiser pour prendre en charge autocompletion
*/

/*
** AUTOCOMPLETION
*/

static int		pos_start(char *input, int start)
{
	int	i;
	int	new_w;
	int	tmp;

	i = 0;
	new_w = 1;
	tmp = 0;
	while (i <= start)
	{
		if (input[i] == '\\')
		{
			if (new_w == 0)
			{
				tmp = i;
				new_w = 1;
			}
			i++;
		}
		else
		{
			if (ft_isspace(input[i]) || input[i] == '|' || input[i] == '&'
					|| input[i] == ';' || input[i] == '/')
				new_w = 0;
			else if (new_w == 0)
			{
				tmp = i;
				new_w = 1;
			}
		}
		i++;
	}
	if (new_w == 1)
		start = tmp;
	return (start);
}

static void	ft_assign_tmp1(int start, int *i, char *input, char **tmp)
{
	*i = 0;
	while (*i < start)
	{
		(*tmp)[*i] = input[*i];
		(*i)++;
	}
}

static void	ft_assign_tmp2(int start, int i, char *input, char **tmp)
{
	while (input[start] != '\0')
	{
		(*tmp)[i] = input[start];
		start++;
		i++;
	}
	(*tmp)[i] = '\0';
}

static char	*ft_add_string(char *input, char **binary, int start)
{
	char	*tmp;
	int		len;
	int		i;
	int		y;

	i = 0;
	ft_printf("path=[%s]\n", *binary);
	ft_printf("input=[%s]\n", input);
	start = pos_start(input, start);
	y = start;
	while (input[y] != '\0' && input[y] == (*binary)[i++])
		y++;
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
	start = start + len;
	ft_assign_tmp2(start, i, input, &tmp);
	ft_printf("line=[%s]\n", tmp);
	return (tmp);
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

static int	dynamic_comp(char **binary, char *input, char **equal, int start)
{
	int		i;
	int		y;
	int		tmp_start;
	char	*tmp;

	tmp_start = pos_start(input, start);
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

/*
** curseur
*/

int			tab_key(char **buff, t_cursor *cursor)
{
	int		ret;
	t_tst	*tst;
	char	**binary;
	char	*input;

	input = NULL;
	if (!cursor->end)
		return (1);
	tst = ft_tst();
	if (!(ret = ft_auto_completion(tst, *buff, &binary, cursor->start)))
		return (del_tst(tst));
	if (ret == 2)
	{
		if (!(input = ft_add_string(*buff, &binary[0], cursor->start)))
		{
			del_tst(tst);
			del_double_char(binary);
			return (0);
		}
		set_string(buff, cursor, input);
		ft_strdel(&input);
	}
	else if (binary && binary[0] != NULL)
	{
		if ((ret = dynamic_comp(binary, *buff, &input, cursor->start)) == 1)
		{
			set_string(buff, cursor, input);
			ft_strdel(&input);
		}
		else if (ret == 0)
		{
			del_tst(tst);
			del_double_char(binary);
			return (0);
		}
		print_double_char(binary);
	}
	del_tst(tst);
	if (binary)
		del_double_char(binary);
	return (1);
}

/*
** END
*/
