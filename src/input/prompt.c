/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 17:12:27 by bprunevi          #+#    #+#             */
/*   Updated: 2019/10/20 11:26:10 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "quote.h"
# define COLOR "\033[38;5;16;48;5;34;m"
# define NCOLOR "\033[38;5;34;48;5;0;m"
# define ERR_COLOR "\033[38;5;16;48;5;124;m"
# define NERR_COLOR "\033[38;5;124;48;5;0;m"
# define RESET "\033[0m"

#include <unistd.h>

static char *quoteword(char c)
{
	if (c == '\'')
		return(ft_strdup("quote "));
	if (c == '\"')
		return(ft_strdup("dquote "));
	if (c == '`')
		return(ft_strdup("bquote "));
	if (c == '{')
		return(ft_strdup("crush "));
	if (c == '(')
		return(ft_strdup("subsh "));
	return(ft_strdup(""));
}

static char *qtbuff_to_text(char *qtbuff)
{
	char *final;

	final = ft_strdup("");
	while (*qtbuff)
		final = ft_strjoinfree(final, quoteword(*(qtbuff++)));
	final = ft_strjoinfree(final, ft_strdup("> "));
	return(final);
}

size_t mkprompt_quote(char *input, char **buff)
{
	char *qtbuff;

	qtbuff = quote_prompt(input);
	if (!qtbuff || !*qtbuff)
		return(0);
	*buff = qtbuff_to_text(qtbuff);
	free(qtbuff);
	return (ft_strlen(*buff));
}

char *mkprompt_intro(size_t ret, size_t *len)
{
	if (!ret)
	{
		*len += 1;
		return(ft_strdup(COLOR" "));
	}
	else
	{
		*len += 1;
		return(ft_strdup(ERR_COLOR" "));
	}
}

char *mkprompt_getcwd(size_t ret, size_t *len)
{
	char *rtn;

	(void) ret;
	rtn = getcwd(NULL, 0);
	*len += ft_strlen(rtn);
	return(rtn);
}

char *mkprompt_outro(size_t ret, size_t *len)
{
	if (!ret)
	{
		*len += 3;
		return(ft_strdup(" "NCOLOR""RESET" "));
	}
	else
	{
		*len += 3;
		return(ft_strdup(" "NERR_COLOR""RESET" "));
	}
}

size_t mkprompt(char **prompt)
{
	size_t len;
	size_t ret;

	len = 0;
	ret = 0;
	*prompt = ft_strnjoinfree(3,
			mkprompt_intro(ret, &len),
			mkprompt_getcwd(ret, &len),
			mkprompt_outro(ret, &len));
	return (len);
}
