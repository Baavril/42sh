/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 15:06:39 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/29 16:10:57 by yberramd         ###   ########.fr       */
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

int		ft_print_history(char **argv);
int		ft_atoi_history(const char *str);
int		ft_execute(char **option);
int		ft_fc(char **option, char **argv);
int		ft_strisnbr(char *str);
int		ft_parser(int argc, char **argv, char *optstring,
						char **option);
void	ft_arg_r(int i, int max);
void	ft_number(int nbr, int nbr2, int max);
void	ft_one_number_w(char *str_nbr, int max, int fd);
void	ft_two_number_w(char **argv, int max, int fd);

#endif
