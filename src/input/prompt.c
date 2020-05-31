/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 17:12:27 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/31 16:20:18 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "quote.h"
#include "error.h"
#include "prompt.h"
#include "shell_variables.h"

extern struct s_svar	*g_svar;
extern int				g_retval;

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
	*len += 3;
	if (!g_retval)
		return (ft_strdup(" "COLOR"~"RESET_TC" "));
	return (ft_strdup(" "ERR_COLOR"~"RESET_TC" "));
}

size_t	mk_prompt(char **prompt, char *prompt_var)
{
	char			*tmp;
	struct s_svar	*voyager;
	size_t			len;

	len = 0;
	tmp = "";
	voyager = g_svar;
	while (voyager)
	{
		if (!(ft_strcmp(voyager->key, prompt_var)))
		{
			tmp = voyager->value;
			break ;
		}
		voyager = voyager->next;
	}
	tmp = mkprompt_expand(tmp, &len);
	if (prompt_var[2] == '1')
		tmp = ft_strnjoinfree(3,
				mkprompt_intro(&len),
				tmp, mkprompt_outro(&len));
	*prompt = tmp;
	return (len);
}

int		ft_check_inhib(char *input)
{
	t_list			*unclosed_inhib;
	int				ret;
	char			str[2];

	unclosed_inhib = NULL;
	if ((ret = quote_check(&unclosed_inhib, input)) == ERR)
	{
		str[0] = *((char *)unclosed_inhib->content);
		str[1] = '\0';
		psherror(e_syntax_error, str, e_parsing_type);
		ft_lstdel(&unclosed_inhib, &ft_lst_strdel);
		return (-1);
	}
	if (unclosed_inhib == NULL && ret != ESC_NL)
		return (0);
	ft_lstdel(&unclosed_inhib, &ft_lst_strdel);
	return (1);
}
