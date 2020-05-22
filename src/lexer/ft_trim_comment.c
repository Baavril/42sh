/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_comment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <tgouedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 13:37:02 by tgouedar          #+#    #+#             */
/*   Updated: 2020/05/22 12:16:44 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "quote.h"

char				*g_input;

static int			ft_update_trig(char *command)
{
	static t_list			*unclosed_inhib = NULL;
	static _Bool			dollar;
	char					open;

	open = (unclosed_inhib) ? *((char*)(unclosed_inhib->content)) : 0;
	if (open == '\\')
	{
		ft_lstpop(&unclosed_inhib, &ft_lst_strdel);
		return (0);
	}
	if (*command == '$')
		dollar = (open != '\'');
	else if (dollar)
	{
		if ((*command == '{' || *command == '(') && !(dollar = 0))
			ft_lstadd(&unclosed_inhib, ft_lstnew(command, 1));
	}
	else if (ft_isin(*command, INHIB))
		ft_treat_inhib(&unclosed_inhib, *command);
	else if (*command == '\\' && !ft_isin(open, QUOTES))
		ft_lstadd(&unclosed_inhib, ft_lstnew(command, 1));
	else if (!(*command))
		ft_lstdel(&unclosed_inhib, &ft_lst_strdel);
	return (unclosed_inhib && *(char*)(unclosed_inhib->content) == '#');
}

static size_t		ft_new_input_len(void)
{
	size_t		i;
	size_t		len;
	int			trig;

	i = 0;
	len = 0;
	trig = 0;
	while (g_input[i])
	{
		trig = ft_update_trig(&g_input[i]);
		if (!trig)
			++len;
		if (g_input[++i] == '\n')
			trig = 0;
	}
	trig = ft_update_trig(&g_input[i]);
	return (len);
}

int					ft_trim_comment(void)
{
	size_t		i;
	size_t		j;
	_Bool		trig;
	char		*new_input;

	i = 0;
	trig = 0;
	j = ft_new_input_len();
	if (!(new_input = ft_strnew(j)))
		return (1);
	j = 0;
	while (g_input[i])
	{
		trig = ft_update_trig(&g_input[i]);
		if (!trig)
			new_input[j++] = g_input[i];
		++i;
	}
	trig = ft_update_trig(&g_input[i]);
	ft_strdel(&g_input);
	g_input = new_input;
	return (0);
}
