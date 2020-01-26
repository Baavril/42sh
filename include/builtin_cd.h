/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:34:46 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/23 18:07:10 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CD_H
# define BUILTIN_CD_H

# define CD_OPT					"+LP"
# define EXEC_SUCCESS			0
# define ERROR					1
# define UNSET_VAR				1
# define NO_PERM				1 //to check
# define NOT_DIR				1 //to check
# define TARGET_NOT_FOUND		1
# define STAT_ERROR				-1

int				ft_get_permission(char *path);
int				ft_gettype(char *path);
char			*ft_get_link_target(char *link_name);
int				ft_is_valid_dir(char *path);
int				ft_get_abspath(char **new_pwd);
int				ft_simplify_path(char **path);
char			*ft_concatenate_path(char *src, char *rel_dst);

#endif
