/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:08:47 by bprunevi          #+#    #+#             */
/*   Updated: 2020/07/08 17:52:53 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "error.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>

extern int g_prefix;

int	i_redirect(t_elem left, t_elem right)
{
	if (g_prefix)
		if (left.v->f(left.v->left, left.v->right) == -1)
			return (-1);
	if (right.v)
		return (right.v->f(right.v->left, right.v->right));
	return (0);
}

int	i_less(t_elem left, t_elem right)
{
	int fd1;

	fd1 = left.c ? *left.c - '0' : 0;
	if (!*right.c)
		psherror(e_ambiguous_redirect, right.c, e_cmd_type);
	else if (!access(right.c, R_OK))
	{
		if (is_regfile(right.c))
			return (open_on_fd(right.c, O_RDONLY, 0, fd1));
		psherror(e_not_a_valid_file, right.c, e_cmd_type);
	}
	else if (!access(right.c, F_OK))
		psherror(e_permission_denied, right.c, e_cmd_type);
	else
		psherror(e_no_such_file_or_directory, right.c, e_cmd_type);
	return (-1);
}

int	i_great(t_elem left, t_elem right)
{
	int		fd1;
	int		resfd;

	fd1 = left.c ? *left.c - '0' : 1;
	if (!*right.c)
		psherror(e_ambiguous_redirect, right.c, e_cmd_type);
	else if (!access(right.c, W_OK))
	{
		if (is_regfile(right.c))
			return (open_on_fd(right.c, O_WRONLY | O_TRUNC, 0, fd1));
		psherror(e_not_a_valid_file, right.c, e_cmd_type);
	}
	else if (!access(right.c, F_OK))
		psherror(e_permission_denied, right.c, e_cmd_type);
	else if ((resfd = open_on_fd(right.c, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH, fd1)) != -1)
		return (resfd);
	else
		psherror(e_permission_denied, right.c, e_cmd_type);
	return (-1);
}

int	i_dgreat(t_elem left, t_elem right)
{
	int fd1;

	fd1 = left.c ? *left.c - '0' : 1;
	if (!*right.c)
		psherror(e_ambiguous_redirect, right.c, e_cmd_type);
	else if (!access(right.c, W_OK))
	{
		if (is_regfile(right.c))
			return (open_on_fd(right.c, O_WRONLY | O_APPEND, 0, fd1));
		psherror(e_not_a_valid_file, right.c, e_cmd_type);
	}
	else if (!access(right.c, F_OK))
		psherror(e_permission_denied, right.c, e_cmd_type);
	else
	{
		return (open_on_fd(right.c,
				O_WRONLY | O_APPEND | O_CREAT, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IROTH, fd1));
	}
	return (-1);
}

int	i_clobber(t_elem left, t_elem right)
{
	return (i_great(left, right));
}
