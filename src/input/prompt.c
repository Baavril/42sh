/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 17:12:27 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/29 16:54:45 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "prompt.h"
#include "quote.h"
#include "shell_variables.h"

# define COLOR "\033[96;m"
# define ERR_COLOR "\033[31;m"
# define BLUE "\033[96;m"
# define RED "\033[96;m"
# define RESET "\033[0m"

extern struct s_svar	*g_svar;
extern int 				g_retval;

size_t mkprompt_quote(char *input, char **buff)
{
	char *qtbuff;
	struct s_svar	*voyager;

	qtbuff = quote_prompt(input);
	if (!qtbuff || !*qtbuff)
		return (0);
	voyager = g_svar;
	while (voyager)
	{
		if (!(ft_strcmp(voyager->key, PS2)))
			*buff = ft_strdup(voyager->value);
		voyager = voyager->next;
	}
	free(qtbuff);
	return (ft_strlen(*buff));
}

char *mkprompt_intro(size_t *len)
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

char *mkprompt_getcwd(size_t *len)
{
	struct s_svar	*voyager;

	voyager = g_svar;
	while (voyager)
	{
		if (!(ft_strcmp(voyager->key, PWD)))
		{
			*len = ft_strlen(voyager->value);
			return(ft_strdup(voyager->value));
		}
		voyager = voyager->next;
	}
	*len = 0;
	return (ft_strdup(""));
}

char *mkprompt_outro(size_t *len)
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

size_t mkprompt(char **prompt)
{
	size_t len;
	size_t ret;

	len = 0;
	ret = 0;
	*prompt = ft_strnjoinfree(3,
			mkprompt_intro(&len),
			mkprompt_getcwd(&len),
			mkprompt_outro(&len));
	ft_printf("[%s]\n", *prompt);
	return (len);
}

char	*search_prompt_intro(t_cursor *cursor)
{
	char *tmp;

	tmp = NULL;
	if (!cursor->match_ret)
	{
		tmp = ft_strdup("(reverse-i-search)`");
		return (tmp);
	}
	tmp = ft_strdup("(failed reverse-i-search)`");
	return (tmp);
}

size_t	search_prompt(t_cursor *cursor, char *buff)
{
	char *intro;
	char *outro;
	char *tmp;
	int len;

	len = 0;
	tmp = (!*buff) ? ft_strdup("") : ft_strdup(buff);
	intro = search_prompt_intro(cursor);
	outro = ft_strdup("': ");
	cursor->prompt = ft_strnjoinfree(3, intro, tmp, outro);
	len = ft_strlen(cursor->prompt);
	return (len);
}
