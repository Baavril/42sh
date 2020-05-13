/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 18:26:13 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/13 16:27:35 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# ifndef O_RDONLY
#  define O_RDONLY 0
# endif

# ifndef O_WRONLY
#  define O_WRONLY 1
# endif

# ifndef O_RDWR
#  define O_RDWR 2
# endif

# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "shell_variables.h"
# include "maths_expansion.h"
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
	SWAP,
	NEW_HIST,
};

enum {
	ARG_L = 1,
	ARG_R = 2,
	ARG_S = 4,
	ARG_N = 8,
	ARG_E = 16,
	ARG_NUMBER = 32,
};

typedef struct			s_history
{
	char				*str;
	struct s_history	*next;
	struct s_history	*previous;
}						t_history;

int						history(int flag, char **line, char **cmd);
int						init_history(t_history *history);
int						delete_history(t_history *history);

int						assign_file_history(int fd, t_history *history,
							int max, char *home);
int						ft_swap_2(t_history **history, char *cmd);
int						get_first(t_history **history, char **cmd);
int						get_last(t_history **history, char **cmd);
int						get_next(t_history **history, char **cmd);
int						get_previous(t_history **history, char **cmd);
int						new_history(t_history **history);
int						assign_max_home(int *max, char **home);
int						delete(t_history *history, int flag);
int						s_exclamation(char **line, t_history *history, int *ret,
																	char *cmd);
int						ft_isseparator(char *str);
int						exclamation_point(char *line, t_history *history,
																	char **cmd);
int						ft_atoi_history2(const char *str);
int						exclamation_p_m_n(const char *line, t_history *h,
																	char **cmd);
int						exclamation_point_number(const char *line, t_history *h,
																	char **c);
int						exclamation_s_history(t_history *history, char *line,
																	char **cmd);
int						ft_search(t_history *history_2, const char *line,
															char **cmd, int f);
int						search_history(t_history *history, char *line,
																	char **cmd);

#endif
