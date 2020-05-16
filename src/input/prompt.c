/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 17:12:27 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/12 15:44:53 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "quote.h"
#include "error.h"
#include "shell_variables.h"

extern struct s_svar	*g_svar;
extern int				g_retval;

int		mkprompt_quote(char *input, char **prompt, size_t *len)
{
	t_list			*unclosed_inhib;
	char			err[2];
	int				ret;

	unclosed_inhib = NULL;
	if ((ret = quote_prompt(&unclosed_inhib, input)) == ERR)
	{
		err[0] = *((char*)(unclosed_inhib->content));
		err[1] = '\0';
		psherror(e_syntax_error, &(err[0]), e_parsing_type);
		ft_lstdel(&unclosed_inhib, &ft_lst_strdel);
		return (-1);
	}
	if (unclosed_inhib == NULL && ret != ESC_NL)
		return (0);
	*prompt = getshvar("PS2");
	*len = ft_strlen(*prompt);
	ft_lstdel(&unclosed_inhib, &ft_lst_strdel);
	return (1);
}

char	*mkprompt_intro(size_t *len)
{
	if (!g_retval)
	{
		*len += 0;
		return (ft_strdup(COLOR""));
	}
	else
	{
		*len += 0;
		return (ft_strdup(ERR_COLOR""));
	}
}

char	*mkprompt_getcwd(size_t *len)
{
	struct s_svar	*voyager;

	voyager = g_svar;
	while (voyager)
	{
		if (!(ft_strcmp(voyager->key, PWD)))
		{
			*len += ft_strlen(voyager->value);
			return (ft_strdup(voyager->value));
		}
		voyager = voyager->next;
	}
	*len = 0;
	return (ft_strdup(""));
}

char	*mkprompt_outro(size_t *len)
{
	if (!g_retval)
	{
		*len += 3;
		return (ft_strdup(" "COLOR"~"RESET_TC" "));
	}
	else
	{
		*len += 3;
		return (ft_strdup(" "ERR_COLOR"~"RESET_TC" "));
	}
}

size_t	mkprompt(char **prompt)
{
	size_t len;

	len = 0;
	*prompt = ft_strnjoinfree(3,
			mkprompt_intro(&len),
			mkprompt_getcwd(&len),
			mkprompt_outro(&len));
	return (len);
}
