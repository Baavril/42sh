/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:49:41 by abarthel          #+#    #+#             */
/*   Updated: 2019/09/25 16:32:10 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETOPT_H
# define FT_GETOPT_H

# ifdef __unix__
#  define RESET_OPTIND 0
# else
#  define RESET_OPTIND 1
# endif

extern char	*g_optarg;
extern int	g_optind;
extern int	g_optopt;
extern int	g_opterr;

int	ft_getopt(int argc, char *const argv[], const char *optstring);

#endif
