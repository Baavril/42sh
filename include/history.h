/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hisotry.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 18:26:13 by yberramd          #+#    #+#             */
/*   Updated: 2019/10/02 14:28:44 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H
# ifndef O_RDONLY
# define O_RDONLY 0
# endif
# ifndef O_WRONLY
# define O_WRONLY 1
# endif
# ifndef O_RDWR
# define O_RDWR 2
# endif 
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "shell_variables.h"
# include "libft.h"

enum {
	INIT,
	DELETE,
	ADD_CMD,
	SEARCH,
	HISTORY_SEARCH,
	FORWARD,
	BACKWARD,
	GET,
	FIRST,
	LAST,
	RESET,
};

enum {
	ARG_L = 1,
	ARG_R = 2,
	ARG_S = 4,
	ARG_N = 8,
	ARG_E = 16,
	ARG_NUMBER = 32,
};

typedef struct	s_history
{
	char	*str;
	struct s_history *next;
	struct s_history *previous;
}				t_history;

int		history(int flag, char **line, char **cmd);
#endif
