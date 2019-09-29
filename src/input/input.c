/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:56:11 by bprunevi          #+#    #+#             */
/*   Updated: 2019/09/29 14:57:29 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "keys.h"
#include "prompt.h"
#include "libft.h"

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

void display_init(int sig)
{
	char buff[16];
	int j;

	j = 0;
	ft_bzero(buff, 16);
#if 0
	if (sig == SIGWINCH)
		ft_printf("%s", tgoto(tgetstr("cm", NULL), 0, g_pi.line)); 
#else
	(void) sig;
#endif
	write(1, "\x1B[6n", 4);
	read(1, &buff, 15);
	while (!ft_isdigit(buff[j]))
		j++;
	g_pi.line = ft_atoi(&buff[j]);
	(g_pi.line)--;
	g_pi.t_col = tgetnum("co");
	g_pi.t_li = tgetnum("li");
}

int display(char *str, int j, int i, char *prompt, int prompt_len)
{
	while (g_pi.t_li == g_pi.line + (i + prompt_len) / g_pi.t_col && g_pi.line--)
		ft_printf("\n");
	ft_printf("%s", tgoto(tgetstr("cm", NULL), 0, g_pi.line)); 
	ft_printf("%s", tgetstr("cd", NULL));
	ft_printf("%s", prompt);
	ft_printf("%s", str ? str : "");
	ft_printf("%s", tgoto(tgetstr("cm", NULL), (j + prompt_len) % g_pi.t_col,  g_pi.line + (j + prompt_len) / g_pi.t_col));
	return(0);
}

int get_stdin(char *prompt, char **buff)
{
	int i;
	int j;
	int prompt_len;
	char c;

	i = 0;
	j = 0;
	*buff = ft_strdup("");
	display_init(0);
	prompt_len = ft_strlen(prompt);
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

	mkprompt(&prompt);
	get_stdin(prompt, buff);
	write(1, "\n", 1);
	while (!mkprompt_quote(*buff, &prompt) && prompt)
	{
		get_stdin(prompt, &tmp);
		*buff = ft_strjoinfree(*buff, tmp);
		write(1, "\n", 1);
	}
	return(0);
}
