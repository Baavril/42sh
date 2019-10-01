/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 17:12:27 by bprunevi          #+#    #+#             */
/*   Updated: 2019/10/01 12:25:26 by bprunevi         ###   ########.fr       */
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

int mkprompt_quote(char *input, char **buff)
{
	char *qtbuff;

	qtbuff = quote_prompt(input);
	if (!qtbuff || !*qtbuff)
		return(0);
	*buff = qtbuff_to_text(qtbuff);
	free(qtbuff);
	return (ft_strlen(*buff));
}

int		mkprompt_intro(char *buff, int ret)
{
	if (!ret)
		ft_strcat(buff, COLOR" ");
	else
		ft_strcat(buff, ERR_COLOR" ");
	return(1);
}

int		mkprompt_outro(char *buff, int ret)
{
	if (!ret)
		ft_strcat(buff, " "NCOLOR""RESET" ");
	else
		ft_strcat(buff, " "NERR_COLOR""RESET" ");
	return(3);
}

int mkprompt(char **prompt)
{
	char *stackbuff[128];
	char *buff;
	int len;

	buff = (char *)stackbuff;
	buff[0] = '\0';
	len = 0;
	len += mkprompt_intro(buff, 0);
	while (*buff)
		buff++;
	getcwd(buff, 128 - sizeof(" "NCOLOR""RESET" "));
	len += ft_strlen(buff);
	len += mkprompt_outro(buff, 0);
	*prompt = ft_strdup((char *)stackbuff);
	return (len);
}
