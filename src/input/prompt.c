/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 17:12:27 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/22 15:07:32 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "quote.h"
#include "error.h"
#include "prompt.h"
#include "shell_variables.h"

#define COLOR "\033[96;m"
#define ERR_COLOR "\033[31;m"
#define RESET "\033[0m"

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

char	*mkprompt_outro(size_t *len)
{
	if (!g_retval)
	{
		*len += 3;
		return (ft_strdup(" "COLOR"~"RESET" "));
	}
	else
	{
		*len += 3;
		return (ft_strdup(" "ERR_COLOR"~"RESET" "));
	}
}

size_t	mkprompt(char **prompt)
{
	char			*tmp;
	struct s_svar	*voyager;
	size_t			len;

	tmp = NULL;
	voyager = g_svar;
	while (voyager)
	{
		if (!(ft_strcmp(voyager->key, PS1)))
		{
			tmp = voyager->value;
			break ;
		}
		voyager = voyager->next;
	}
	if (!tmp)
		tmp = "";
	len = 0;
	*prompt = ft_strnjoinfree(3,
			mkprompt_intro(&len),
			mkprompt_expand(tmp, &len),
			mkprompt_outro(&len));
	return (len);
}
