/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:31:43 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/23 17:54:06 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "auto_completion.h"
#include "input.h"
#include "keys.h"

static void	ft_new_word(int i, char *input, int *tmp, int *new_w)
{
	if (ft_isspace(input[i]) || input[i] == '|' || input[i] == '&'
			|| input[i] == ';' || input[i] == '/')
		(*new_w) = 0;
	else if ((*new_w) == 0)
	{
		(*tmp) = i;
		(*new_w) = 1;
	}
}

int			pos_start2(char *input, int start)
{
	int	i;
	int	new_w;
	int	tmp;

	i = 0;
	new_w = 1;
	tmp = 0;
	while (i < start)
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
			ft_new_word(i, input, &tmp, &new_w);
		i++;
	}
	if (new_w == 1)
		start = tmp;
	return (start);
}

/*
** curseur
*/

static int	ft_double_char(char **buff, char **binary, t_tst *tst,
							t_cursor *cursor)
{
	int		ret;
	char	*input;

	input = NULL;
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
	return (1);
}

int			tab_key(char **buff, t_cursor *cursor)
{
	int		ret;
	t_tst	*tst;
	char	**binary;

	if (!cursor->end)
		return (1);
	tst = ft_tst();
	if (!(ret = ft_auto_completion(tst, *buff, &binary, cursor->start)))
		return (del_tst(tst));
	if (ret == 2)
	{
		if (!ft_string(buff, binary, tst, cursor))
			return (0);
	}
	else if (binary && binary[0] != NULL)
		if (!ft_double_char(buff, binary, tst, cursor))
			return (0);
	del_tst(tst);
	if (binary)
		del_double_char(binary);
	return (1);
}
