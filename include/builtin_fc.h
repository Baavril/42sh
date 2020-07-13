/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 15:06:39 by yberramd          #+#    #+#             */
/*   Updated: 2020/07/13 18:51:39 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_FC_H
# define BUILTIN_FC_H

# include <unistd.h>
# include <getopt.h>
# include "history.h"
# include "libft.h"
# include "ft_getopt.h"
# include "parser.h"

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

typedef struct		s_fc
{
	int				i;
	int				found;
	char			*cmd;
}					t_fc;

int		reset_arg(t_fc *explorer);
int		ft_print_history(char **argv);
int		ft_atoi_history(const char *str);
int		ft_execute(char **option);
int		ft_fc(char **option, char **argv);
int		ft_strisnbr(char *str);
int		ft_parser(int argc, char **argv, char *optstring,
						char **option);
void	ft_arg_r(int i, int max);
int		f_arg_nbr(char **argv, int max, int reset);
void	ft_number(int nbr, int nbr2, int max);
void	fc_search_string(char **argv, int max);
void	ft_one_number_w(char *str_nbr, int fd);
void	ft_two_number_w(char **argv, int max, int fd);

#endif
