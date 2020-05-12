/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 15:06:39 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/12 15:34:18 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_FC_h
# include <unistd.h>
# include <getopt.h>
# include "history.h"
# include "libft.h"
# include "ft_getopt.h"
# include "parser.h"

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

int	ft_print_history(int arg, char **argv);
int	ft_atoi_history(const char *str);
int	ft_strisnbr(char *str);

#endif
