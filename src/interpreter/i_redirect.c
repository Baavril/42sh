/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:08:47 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/22 15:03:27 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <unistd.h>
#include "error.h"
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
		ft_dprintf(STDERR_FILENO, "42sh: %s: Redirection ambigue\n", right.c);
	else if (!access(right.c, R_OK))
	{
		if (is_regfile(right.c))
			return (open_on_fd(right.c, O_RDONLY, 0, fd1));
		ft_dprintf(STDERR_FILENO, "42sh: %s: not a valid file\n", right.c);
	}
	else if (!access(right.c, F_OK))
		psherror(e_permission_denied, right.c, e_cmd_type);
	else
		ft_dprintf(STDERR_FILENO, "42sh: %s: No such file or directory\n",
		right.c);
	return (-1);
}

int	i_great(t_elem left, t_elem right)
{
	int		fd1;
	int		resfd;

	fd1 = left.c ? *left.c - '0' : 1;
	if (!*right.c)
		ft_dprintf(STDERR_FILENO, "42sh: %s: Redirection ambigue\n", right.c);
	else if (!access(right.c, W_OK))
	{
		if (is_regfile(right.c))
			return (open_on_fd(right.c, O_WRONLY | O_TRUNC, 0, fd1));
		ft_dprintf(STDERR_FILENO, "42sh: %s: not a valid file\n", right.c);
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
		ft_dprintf(STDERR_FILENO, "42sh: %s: Redirection ambigue\n", right.c);
	else if (!access(right.c, W_OK))
	{
		if (is_regfile(right.c))
			return (open_on_fd(right.c, O_WRONLY | O_APPEND, 0, fd1));
		ft_dprintf(STDERR_FILENO, "42sh: %s: not a valid file\n", right.c);
	}
	else if (!access(right.c, F_OK))
		ft_dprintf(STDERR_FILENO, "42sh: %s: forbidden acess\n", right.c);
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
