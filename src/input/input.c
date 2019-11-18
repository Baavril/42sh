/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:56:11 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/18 12:39:43 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "keys.h"
#include "prompt.h"
#include "display.h"
#include "history.h"

#include <unistd.h>
#include <stdio.h>
#include <term.h>
#include <curses.h>
#include <stdint.h>

t_dispatch_keys		g_dispatch_keys[] =
{
	{NULL, &left_arrow},
	{NULL, &right_arrow},
	{NULL, &up_arrow},
	{NULL, &down_arrow},
	{NULL, &delete_key},
	{NULL, &home_key},
	{NULL, &next_word},
	{NULL, &previous_word},
	{NULL, &end_key},
	{NULL, &select_key},
	{NULL, &paste_key},
	{NULL, &search_history},
	{NULL, NULL}
};

void	update_buff(char *match, char **buff, t_cursor *cursor)
{
	size_t len;

	len = 0;
	ft_bzero(*buff, ft_strlen(*buff));
	if (match)
	{
		len = ft_strlen(match);
		if (cursor->end < len)
			*buff = buff_realloc(*buff, len);
		ft_strcpy(*buff, match);
	}
	cursor->end = len;
}

int	search_history(char **buff, t_cursor *cursor)
{
	int i;
	char *match;
	union	u_tc termcaps;

	i = 0;
	match = NULL;
	inside_history = NULL;
	ft_strdel(&(cursor->prompt));
	ft_init_cursor(cursor);
	ft_bzero(*buff, ft_strlen(*buff));
	while (1)
	{
		ft_strdel(&(cursor->prompt));
		cursor->prompt_len = search_prompt(cursor, *buff);
		display(match, cursor);
		ft_bzero(termcaps.buff, COUNT_KEY);
		read(STDIN_FILENO, termcaps.buff, COUNT_KEY);
		if (ft_isprint(termcaps.key))
		{
			cursor->start = ft_strlen(*buff);
			normal_char(buff, cursor, termcaps.key);
			match = get_history(buff, cursor);
		}
		else if (termcaps.key == BACKSPACE)
		{
			cursor->start = ft_strlen(*buff);
			backspace_key(buff, cursor);
			match = get_history(buff, cursor);
		}
		else if (termcaps.key == TABULATION)
		{
			tab_key(buff, cursor);
			ft_strdel(&(cursor->prompt));
			cursor->prompt_len = mkprompt(&(cursor->prompt));
			history(RESET, buff, NULL);
			return (1);
		}
		else if (termcaps.key == ENTER)
		{
			update_buff(match, buff, cursor);
			history(RESET, buff, NULL);
			return (0);
		}
		else if (termcaps.key == '\033')
		{
			i = 0;
			while (g_dispatch_keys[i].key_path != NULL && ft_strcmp(g_dispatch_keys[i].key_path, "1;5A"))
			{
				if (ft_strncmp(g_dispatch_keys[i].key_path, &termcaps.buff[2], ft_strlen(g_dispatch_keys[i].key_path)) == 0)
				{
					g_dispatch_keys[i].function_call(&match, cursor);
					update_buff(match, buff, cursor);
					ft_strdel(&(cursor->prompt));
					cursor->prompt_len = mkprompt(&(cursor->prompt));
					history(RESET, buff, NULL);
					return (1);
				}
				i++;
			}
		}
	}
	return (1);
}

int toggle_termcaps(void)
{
	struct termios term;

	term.c_cc[VMIN] = 1; /* si VTIME = 0 et ICANON desactive VMIN determine le nombre d'octets lus par read */
	term.c_cc[VTIME] = 0;
	if (tcgetattr(STDIN_FILENO, &term) < 0)
	{
		printf("Error tcgetattr");
		return(1);
	}
	term.c_lflag ^= (ECHO | ICANON | ISIG | IEXTEN);
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &term) < 0)
	{
		printf("Error tcsetattr");
		return(1);
	}
	if (tgetent(NULL, getenv("TERM")) != 1)
	{
		printf("Error tgetent");
		return(1);
	}
	return(0);
}

int	ft_init_tab(void)
{
	if (!(g_dispatch_keys[0].key_path = tgetstr("kl", NULL) + 2))
		return (1);
	if (!(g_dispatch_keys[1].key_path = tgetstr("kr", NULL) + 2))
		return (1);
	if (!(g_dispatch_keys[2].key_path = tgetstr("ku", NULL) + 2))
		return (1);
	if (!(g_dispatch_keys[3].key_path = tgetstr("kd", NULL) + 2))
		return (1);
	if (!(g_dispatch_keys[4].key_path = tgetstr("kD", NULL) + 2))
		return (1);
	if (!(g_dispatch_keys[5].key_path = tgetstr("kh", NULL) + 2))
		return (1);
	if (!(g_dispatch_keys[6].key_path = tgetstr("kN", NULL) + 2))
		return (1);
	if (!(g_dispatch_keys[7].key_path = tgetstr("kP", NULL) + 2))
		return (1);
	if (!(g_dispatch_keys[8].key_path = "F\0"))
		return (1);
	if (!(g_dispatch_keys[9].key_path = "1;2A"))
		return (1);
	if (!(g_dispatch_keys[10].key_path = "1;2B"))
		return (1);
	if (!(g_dispatch_keys[11].key_path = "1;5A"))
		return (1);
	return (0);
}


int	get_stdin(t_cursor *cursor, char **buff)
{
	int	i;
	union	u_tc termcaps;

	i = 0;
	if (ft_init_tab() == 1)
		return (1);
	inside_history = NULL;
	*buff = ft_strdup("");
	while (1)
	{
		display(*buff, cursor);
		ft_bzero(termcaps.buff, COUNT_KEY);
		read(STDIN_FILENO, termcaps.buff, COUNT_KEY);
		if (ft_isprint(termcaps.key))
			normal_char(buff, cursor, termcaps.key);
		else if (termcaps.key_c == CTRL_L)
			ft_putstr(tgetstr("ho", NULL));
		else if (termcaps.key == BACKSPACE)
			backspace_key(buff, cursor);
		else if (termcaps.key == TABULATION)
			tab_key(buff, cursor);
		else if (termcaps.key == ENTER)
		{
			ft_strdel(&inside_history);
			return(0);
		}
		else if (termcaps.key == '\033')
		{
			i = 0;
			while (g_dispatch_keys[i].key_path != NULL)
			{
				if (ft_strncmp(g_dispatch_keys[i].key_path, &termcaps.buff[2], ft_strlen(g_dispatch_keys[i].key_path)) == 0)
				{
					if (((g_dispatch_keys[i].function_call)(buff, cursor)) == 0)
					{
						ft_strdel(&cursor->prompt);
						return (0);
					}
					break ;
				}
				i++;
			}
		}
	}
	return(1);
}

void	ft_init_cursor(t_cursor *cursor)
{
	cursor->prompt = NULL;
	cursor->in = SIZE_MAX;
	cursor->start = 0;
	cursor->end = 0;
	cursor->match_ret = 0;
	cursor->prompt_len = 0;
}

int read_command(char **buff)
{
	char *tmp;
	t_cursor cursor;

	ft_init_cursor(&cursor);
	if (!isatty(STDIN_FILENO))
		return(1);
	if (toggle_termcaps())
		return(2);
	cursor.prompt_len = mkprompt(&(cursor.prompt));
	get_stdin(&cursor, buff);
	write(1, "\n", 1);
	ft_init_cursor(&cursor);
	while (**buff && (cursor.prompt_len = mkprompt_quote(*buff, &(cursor.prompt))))
	{
		get_stdin(&cursor, &tmp);
		*buff = ft_strjoinfree(*buff, tmp);
		ft_strdel(&(cursor.prompt));
		write(1, "\n", 1);
		ft_init_cursor(&cursor);
	}
	ft_strdel(&(cursor.prompt));
	toggle_termcaps();
	return(0);
}
