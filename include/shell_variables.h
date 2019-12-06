/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 09:48:01 by abarthel          #+#    #+#             */
/*   Updated: 2019/12/03 16:46:35 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_VARIABLES_H
# define SHELL_VARIABLES_H

/* Keys of internal variables */

# define PS1	"PS1="
# define PS2	"PS2="
# define PS3	"PS3="
# define PS4	"PS4="
# define HISTSIZE	"HISTSIZE="

/* Values of internal variables */

# define PS1V	"prompt->"
# define PS2V	"quote> "
# define PS3V	"script> "
# define PS4V	"heredoc> "
# define HISTSIZEV	"1000"

extern struct s_svar *g_svar;

struct		s_svar
{
	char			*str;
	char			*key;
	char			*value;
	struct s_svar	*next;
};

int	init_shellvars(char **env);

#endif
