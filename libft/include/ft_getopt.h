/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:49:41 by abarthel          #+#    #+#             */
/*   Updated: 2020/01/15 18:10:03 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETOPT_H
# define FT_GETOPT_H

# ifdef __unix__
#  define RESET_OPTIND 0
# else
#  define RESET_OPTIND 1
# endif

int			ft_getopt(int argc, char *const argv[], const char *optstring);

#endif
