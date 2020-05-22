/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 11:16:45 by tgouedar          #+#    #+#             */
/*   Updated: 2020/05/22 12:19:01 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "quote.h"

void					ft_lst_strdel(void *content, size_t content_size)
{
	ft_memset(content, 0, content_size);
	free(content);
}

static int				ft_close_match(char open, char inhib)
{
	if (open == inhib)
		return (ft_isin(open, QUOTES));
	if (open == '(')
		return ((inhib == ')'));
	if (open == '[')
		return ((inhib == ']'));
	if (open == '{')
		return ((inhib == '}'));
	if (open == '#')
		return ((inhib == '\n'));
	return (0);
}

int						ft_treat_inhib(t_list **unclosed_inhib, char inhib)
{
	char	open;

	open = (*unclosed_inhib) ? *((char*)((*unclosed_inhib)->content)) : 0;
	if (ft_isin(open, CLOSE))
		return (1);
	if (!open && ft_isin(inhib, CLOSE))
	{
		ft_lstadd(unclosed_inhib, ft_lstnew(&inhib, 1));
		return (1);
	}
	if (ft_close_match(open, inhib))
		ft_lstpop(unclosed_inhib, &ft_lst_strdel);
	else if (inhib == '#')
	{
		if (!ft_isin(open, INHIB_COM))
			ft_lstadd(unclosed_inhib, ft_lstnew(&inhib, 1));
	}
	else if (!ft_isin(open, QUOTES) && inhib != '\n')
		ft_lstadd(unclosed_inhib, ft_lstnew(&inhib, 1));
	return (0);
}

static void				ft_inhib_exception(t_list **unclosed_inhib,
														char **command, char open)
{
	if (**command == '$' && open != '\'')
	{
		if (*(*command + 1) == '{' || *(*command + 1) == '(')
			ft_lstadd(unclosed_inhib, ft_lstnew(++(*command), 1));
	}
}

int						quote_prompt(t_list **unclosed_inhib, char *command)
{
	char	open;

	while (*command)
	{
		open = ((*unclosed_inhib)) ? *((char*)((*unclosed_inhib)->content)) : 0;
		if (*command == '\\')
		{
			if (open != '\'')
				command++;
			if (!(*command))
				return (ESC_NL);
		}
		else if (*command == '$')
			ft_inhib_exception(unclosed_inhib, &command, open);
		else if (ft_isin(*command, INHIB))
		{
			if (ft_treat_inhib(unclosed_inhib, *command) == 1)
				return (ERR);
		}
		command++;
	}
	if (*unclosed_inhib && *((char*)((*unclosed_inhib)->content)) == '#')
		ft_lstpop(unclosed_inhib, &ft_lst_strdel);
	return (NO_ERR);
}
