/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:56:11 by bprunevi          #+#    #+#             */
/*   Updated: 2019/10/15 16:42:59 by bprunevi         ###   ########.fr       */
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

int toggle_termcaps()
{
	struct termios term;

	tcgetattr(0, &term);
#if 0
	if (term.c_lflag & ECHOE)
		ft_printf("%d : %s\n", ECHOE, "ECHOE");
	if (term.c_lflag & ECHO)
		ft_printf("%d : %s\n", ECHO, "ECHO");
	if (term.c_lflag & ECHONL)
		ft_printf("%d : %s\n", ECHONL, "ECHONL");
	if (term.c_lflag & ISIG)
		ft_printf("%d : %s\n", ISIG, "ISIG");
	if (term.c_lflag & ICANON)
		ft_printf("%d : %s\n", ICANON, "ICANON");
	if (term.c_lflag & IEXTEN)
		ft_printf("%d : %s\n", IEXTEN, "IEXTEN");
	if (term.c_lflag & TOSTOP)
		ft_printf("%d : %s\n", TOSTOP, "TOSTOP");
	if (term.c_lflag & NOFLSH)
		ft_printf("%d : %s\n", NOFLSH, "NOFLSH");
#endif
	term.c_lflag ^= ECHO;
	term.c_lflag ^= ICANON;
	tcsetattr(0, 0, &term);
	tgetent(NULL, getenv("TERM"));
	return(0);
}

int get_stdin(char *prompt, int prompt_len, char **buff)
{
	int i;
	int j;
	int u;
	char c;

	i = 0;
	j = 0;
	u = -1;
	*buff = ft_strdup("");
	display(*buff, j, i, -1, prompt, prompt_len);
	while (1)
	{
		read(0, &c, 1);
		if (c != 'u' && c != 'p' && ft_isprint(c))
			normal_char(buff, &j, &i, c);
		else if (c == '\177')
			backspace_key(buff, &j, &i);
		else if (c == '\t')
			tab_key(buff, &j, &i);
		else if (c == '\033')
			escape_char(buff, &j, &i, &u);
		else if (c == '\n' && !display(*buff, i, i, -1, prompt, prompt_len))
			return(0);
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
	toggle_termcaps();
	prompt_len = mkprompt(&prompt);
	get_stdin(prompt, prompt_len, buff);
	write(1, "\n", 1);
	while (**buff && (prompt_len = mkprompt_quote(*buff, &prompt)))
	{
		get_stdin(prompt, prompt_len, &tmp);
		*buff = ft_strjoinfree(*buff, tmp);
		write(1, "\n", 1);
	}
	toggle_termcaps();
	ft_strdel(&prompt);
	return(0);
}
