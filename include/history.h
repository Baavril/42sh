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
};
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# ifndef O_RDONLY
# define O_RDONLY 0
# endif
# ifndef O_WRONLY
# define O_WRONLY 1
# endif
# ifndef O_RDWR
# define O_RDWR 2
# endif 

typedef struct	s_history
{
	char	*str;
	struct s_history *next;
	struct s_history *previous;
}				t_history;

int		history(int flag, char **line, char **cmd);
#endif
