/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 18:13:49 by abarthel          #+#    #+#             */
/*   Updated: 2020/02/29 16:00:12 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include <limits.h>

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

char			*short_logical_path(char **cwd);
char			*short_physical_path(char **cwd);

extern char		g_pwd[PATH_MAX];

#endif
