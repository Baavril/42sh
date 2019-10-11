/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:56:11 by bprunevi          #+#    #+#             */
/*   Updated: 2019/10/11 15:05:45 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "keys.h"
#include "prompt.h"
#include "libft.h"
#include "display.h"

#include <unistd.h>
#include <term.h>
#include <curses.h>
#include <signal.h>

int init_termcaps()
{
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag = 0;
	tcsetattr(0, 0, &term);
	tgetent(NULL, getenv("TERM"));
	return(0);
}

int get_stdin(char *prompt, int prompt_len, char **buff)
{
	int i;
	int j;
	char c;

	i = 0;
	j = 0;
	*buff = ft_strdup("");
	display(*buff, j, i, prompt, prompt_len);
	while (1)
	{
		read(0, &c, 1);
		if (ft_isprint(c))
			normal_char(buff, &j, &i, c);
		else if (c == '\177')
			backspace_key(buff, &j, &i);
		else if (c == '\033')
			escape_char(buff, &j, &i);
		else if (c == '\n' && !display(*buff, i, i, prompt, prompt_len))
			return(0);
		display(*buff, j, i, prompt, prompt_len);
	}
	return(1);
}

int read_command(char **buff)
{
	char *prompt;
	char *tmp;
	int prompt_len;

	if (!isatty(0))
		return(1);
	prompt_len = mkprompt(&prompt);
	get_stdin(prompt, prompt_len, buff);
	write(1, "\n", 1);
	while ((prompt_len = mkprompt_quote(*buff, &prompt)))
	{
		get_stdin(prompt, prompt_len, &tmp);
		*buff = ft_strjoinfree(*buff, tmp);
		write(1, "\n", 1);
	}
	return(0);
}
