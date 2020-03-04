/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 09:48:01 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/29 16:30:37 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_VARIABLES_H
# define SHELL_VARIABLES_H

# include "libft.h"

# define SUCCESS		0
# define ERROR			-1
# define EQUAL			'='

/*
** Keys of internal variables
*/

# define PS1			"PS1="
# define PS2			"PS2="
# define PS3			"PS3="
# define PS4			"PS4="
# define SH				"42sh="
# define PPID			"PPID="
# define PID			"PID="
# define OPTERR			"OPTERR="
# define OPTIND			"OPTIND="
# define HISTSIZE		"HISTSIZE="
# define HISTFILE		"HISTFILE="
# define PWD			"PWD="

/*
** Values of internal variables
*/

# define PS1V			"42sh> "
# define PS2V			"> "
# define PS3V			"#? "
# define PS4V			"$> "
# define OPTERRV		"1"
# define OPTINDV		"1"
# define HISTSIZEV		"1000"
# define HISTFILEV		"/.42sh_history"

struct					s_svar
{
	char				*str;
	char				*key;
	char				*value;
	int					exp;
	struct s_svar		*next;
};

struct					s_pos
{
	char				*str;
	char				*key;
	char				*value;
	int					exp;
	struct s_pos		*next;
};

int						setenvvar(char *key, char *value);
int						init_shell_vars(char **env);
char					*get_key(char *var);
char					*ft_strdupto(char *str, char c);
char					*ft_strdupfm(char *str, char c);

void					setenvnod(struct s_svar *new_back);

int						checkvarlst(char *argv);
struct s_svar			*newnodshell(char *env, int exp);

char					*ft_strdupfm(char *str, char c);
char					*ft_strdupto(char *str, char c);

int						set_positional_params(char **tokens);

int						update_prompt_var(void);
int						update_intern_vars(void);
int						ft_strplen(char *str);

#endif
