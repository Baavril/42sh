/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:56:11 by bprunevi          #+#    #+#             */
/*   Updated: 2019/10/20 11:40:58 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "keys.h"
#include "prompt.h"
#include "display.h"

#include <unistd.h>
#include <term.h>
#include <curses.h>
#include <stdint.h>

int toggle_termcaps()
{
	struct termios term;

	if (tcgetattr(0, &term))
		return(1);
	term.c_lflag ^= ECHO;
	term.c_lflag ^= ICANON;
	if (tcsetattr(0, 0, &term))
		return(1);
	if (tgetent(NULL, getenv("TERM")) != 1)
		return(1);
	return(0);
}

int get_stdin(char *prompt, int prompt_len, char **buff)
{
	size_t i;
	size_t j;
	size_t u;
	char c;

	i = 0;
	j = 0;
	u = SIZE_MAX;
	inside_history = NULL;
	*buff = ft_strdup("");
	display(*buff, j, i, SIZE_MAX, prompt, prompt_len);
	while (1)
	{
		if (read(0, &c, 1) == -1)
			return(-1);
		if (ft_isprint(c))
			normal_char(buff, &j, &i, c);
		else if (c == '\177')
			backspace_key(buff, &j, &i);
		else if (c == '\t')
			tab_key(buff, &j, &i);
		else if (c == '\033')
			escape_char(buff, &j, &i, &u);
		else if (c == '\n')
		{
			display(*buff, i, i, SIZE_MAX, prompt, prompt_len);
			ft_strdel(&inside_history);
			return(0);
		}
		display(*buff, j, i, u, prompt, prompt_len);
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
	if (toggle_termcaps())
		return(2);
	prompt_len = mkprompt(&prompt);
	get_stdin(prompt, prompt_len, buff);
	write(1, "\n", 1);
	while (**buff && (prompt_len = mkprompt_quote(*buff, &prompt)))
	{
		get_stdin(prompt, prompt_len, &tmp);
		*buff = ft_strjoinfree(*buff, tmp);
		write(1, "\n", 1);
	}
	ft_strdel(&prompt);
	toggle_termcaps();
	return(0);
}
