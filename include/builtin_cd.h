/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:34:46 by tgouedar          #+#    #+#             */
/*   Updated: 2020/05/25 16:47:47 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CD_H
# define BUILTIN_CD_H

# define CD_OPT					"+LP"
# define EXEC_SUCCESS			0
# define ERROR					1
# define UNSET_OLDPWD			1
# define UNSET_HOME				2
# define NO_PERM				3
# define NOT_DIR				4
# define TARGET_NOT_FOUND		5
# define EXCEED_LINK_LVL		6
# define TOO_MANY_ARG			7
# define STAT_ERROR				-1

# define LINK_LVL				50

int				ft_get_permission(char *path);
int				ft_gettype(char *path);
int				ft_get_targettype(char *path);
char			*ft_get_link_target(char *link_name);
int				ft_is_valid_dir(char *path);
int				ft_get_abspath(char **new_pwd);
int				ft_simplify_path(char **path, int opt_p);
char			*ft_concatenate_path(char *src, char *rel_dst);
int				ft_pcderror(int error_type, char *arg);

#endif
