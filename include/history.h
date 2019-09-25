/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hisotry.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 18:26:13 by yberramd          #+#    #+#             */
/*   Updated: 2019/09/11 14:46:20 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H
# define INIT 1
# define DELETE 2
# define ADD_CMD 3
# define SEARCH 4
# define HISTORY_SEARCH 5
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

int		history(int flag, char *line, char **cmd);
#endif
