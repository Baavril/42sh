/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:31:43 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/08 11:57:13 by tgouedar         ###   ########.fr       */
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

static int	pos_start(char *input, int start)
{
	if (ft_isspace(input[start]) || input[start] == '/' || input[start] == '|'
			|| input[start] == '&' || input[start] == ';')
		start--;
	if (!ft_isspace(input[start]))
	{
		while (start > 0 && !ft_isspace(input[start]) && input[start] != '/'
				&& !(input[start] == '|' || input[start] == '&' ||
					input[start] == ';'))
			start--;
		if (ft_isspace(input[start]) || input[start] == '/'
				|| input[start] == '|' || input[start] == '&'
				|| input[start] == ';')
			start++;
	}
	return (start);
}

static char	*ft_add_string(char *input, char **binary, int start)
{
	char	*tmp;
	int		len;
	int		i;
	int		y;

	i = 0;
	start = pos_start(input, start);
	y = start;
	while (input[y] != '\0' && input[y] == (*binary)[i])
	{
		y++;
		i++;
	}
	len = ft_strlen((*binary)) - i;
	if (!(tmp = (char*)malloc(sizeof(char) * (len + ft_strlen(input) + 1))))
		return (NULL);
	len = i;
	i = 0;
	while (i < start)
	{
		tmp[i] = input[i];
		i++;
	}
	y = 0;
	while ((*binary)[y] != '\0')
	{
		tmp[i] = (*binary)[y];
		i++;
		y++;
	}
	start = start + len;
	while (input[start] != '\0')
	{
		tmp[i] = input[start];
		start++;
		i++;
	}
	tmp[i] = '\0';
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
		tmp = binary[i++];
	}
	if (y == 0 || y == -1)
		return (2);
	y += ft_strlen_modif(&input[tmp_start]);
	if (!(tmp = (char*)malloc(sizeof(char) * (y + 1))))
		return (0);
	assign_tmp(tmp, binary[0], &input[tmp_start], y);
	*equal = ft_add_string(input, &tmp, start);
	ft_strdel(&tmp);
	return ((*equal) ? 1 : 0);
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
	{
		del_tst(tst);
		return (0);
	}
	del_tst(tst);
	if (ret == 2)
	{
		if (!(input = ft_add_string(*buff, &binary[0], cursor->start)))
		{
			del_double_char(binary);
			return (0);
		}
		set_string(buff, cursor, input);
		ft_strdel(&input);
	}
	else if ((binary) && binary[0] != NULL)
	{
		if ((ret = dynamic_comp(binary, *buff, &input, cursor->start)) == 1)
		{
			set_string(buff, cursor, input);
			ft_strdel(&input);
		}
		else if (ret == 0)
		{
			del_double_char(binary);
			return (0);
		}
		print_double_char(binary);
	}
	if (binary)
		del_double_char(binary);
	return (1);
}

/*
** END
*/
