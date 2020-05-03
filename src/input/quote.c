/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 11:16:45 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/01 11:15:54 by tgouedar         ###   ########.fr       */
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
	if (open =='(')
		return ((inhib == ')'));
	if (open =='[')
		return ((inhib == ']'));
	if (open =='{')
		return ((inhib == '}'));
	return (0);
}

static int		ft_treat_inhib(t_list **unclosed_inhib, char inhib)
{
	char	open;

	open = (*unclosed_inhib) ? *((char*)((*unclosed_inhib)->content)) : 0;
	if (ft_isin(open, CLOSE)) // check d'erreur pour voir si on a stacké une fermeture
		return (1);
	if (!open && ft_isin(inhib, CLOSE)) // cas ou l'on stack une fermeture
	{
		ft_lstadd(unclosed_inhib, ft_lstnew(&inhib, 1));
		return (1);
	}
	if (ft_close_match(open, inhib))
		ft_lstpop(unclosed_inhib, &ft_lst_strdel);
	else if (open != '\'' && open != '\"')
		ft_lstadd(unclosed_inhib, ft_lstnew(&inhib, 1));
	return (0);
}

int			quote_prompt(t_list **unclosed_inhib, char *command)
{
	while (*command)
	{
		if (*command == '\\')
		{
			if (!(*unclosed_inhib)
			|| *((char*)((*unclosed_inhib)->content)) != '\'')
				command++;
			if (!(*command)) // cas du '\' en fin de ligne
				return (ESC_NL);
		}
		else if (*command == '$')
		{
			if (!(*unclosed_inhib
			&& *((char*)((*unclosed_inhib)->content)) == '\'')
			&& *(++command) == '{')
				ft_lstadd(unclosed_inhib, ft_lstnew(command, 1));
		}
		else if (ft_isin(*command, INHIB))
		{
			if (ft_treat_inhib(unclosed_inhib, *command) == 1)
				return (ERR);
		}
		command++;
	}
	return (NO_ERR);
}
