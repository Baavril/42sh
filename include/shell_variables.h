/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 09:48:01 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/19 12:51:15 by tgouedar         ###   ########.fr       */
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
# define HISTSIZE		"HISTSIZE="

/*
** Values of internal variables
*/

# define PS1V			"prompt->"
# define PS2V			"quote> "
# define PS3V			"script> "
# define PS4V			"heredoc> "
# define HISTSIZEV		"1000"

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
void					ft_listadd_back(struct s_svar *new_back);
char					*get_key(char *var);
char					*ft_strdupto(char *str, char c);
char					*ft_strdupfm(char *str, char c);

void					ft_lstadd_back(t_list **alst, t_list *new_back);
void					setenvnod(struct s_svar *new_back);

int						checkvarlst(char *argv);
struct s_svar			*newnodshell(char *env, int exp);

char					*ft_strdupfm(char *str, char c);
char					*ft_strdupto(char *str, char c);

#endif
