/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:08:47 by bprunevi          #+#    #+#             */
/*   Updated: 2019/12/23 17:14:39 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#define CREATE_RIGHTS S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

int open_on_fd(const char *path, int o_flags, mode_t mode, int final_fd)
{
	int open_fd;

	if ((open_fd = open(path, o_flags, mode)) != -1)
	{
		dup2(open_fd, final_fd);
		close(open_fd);
		return(final_fd);
	}
	return(-1);
}

int	i_less(t_elem left, t_elem right)
{
	int fd1;

	fd1 = left.c ? *left.c - '0' : 0;
	if (!access(right.c, R_OK))
	{
		if (is_regfile(right.c))
			return (open_on_fd(right.c, O_RDONLY, 0, fd1));
		ft_printf("%s exists and is not a regular file\n", right.c);
	}
	else if (!access(right.c, F_OK))
		ft_printf("%s exists but is not a readable file\n", right.c);
	else
		ft_printf("%s does not exist\n", right.c);
	return (-1);
}

int	i_lessand(t_elem left, t_elem right)
{
	int fd1;

	fd1 = left.c ? *left.c - '0' : 0;
	if (dup2(*right.c - '0', fd1) != -1)
		return (fd1);
	ft_printf("error : %s : incorrect fd\n", right.c);
	return (-1);
}

int	i_great(t_elem left, t_elem right)
{
	int fd1;

	fd1 = left.c ? *left.c - '0' : 1;
	if (!access(right.c, W_OK))
	{
		if (is_regfile(right.c))
			return (open_on_fd(right.c, O_WRONLY, 0, fd1));
		ft_printf("%s exists and is not a regular file\n", right.c);
	}
	else if (!access(right.c, F_OK))
		ft_printf("%s exists but is not a writeable file\n", right.c);
	else
		return (open_on_fd(right.c, O_WRONLY | O_CREAT, CREATE_RIGHTS, fd1));
	return (-1);
}
int	i_dgreat(t_elem left, t_elem right)
{
	int fd1;

	fd1 = left.c ? *left.c - '0' : 1;
	if (!access(right.c, W_OK))
	{
		if (is_regfile(right.c))
			return (open_on_fd(right.c, O_WRONLY | O_APPEND, 0, fd1));
		ft_printf("%s exists and is not a regular file\n", right.c);
	}
	else if (!access(right.c, F_OK))
		ft_printf("%s exists but is not a writeable file\n", right.c);
	else
		return (open_on_fd(right.c, O_WRONLY | O_APPEND | O_CREAT, CREATE_RIGHTS, fd1));
	return (-1);
}

int	i_greatand(t_elem left, t_elem right)
{
	int fd1;

	fd1 = left.c ? *left.c - '0' : 1;
	if (dup2(*right.c - '0', fd1) != -1)
		return (fd1);
	ft_printf("error : %s : incorrect fd\n", right.c);
	return (-1);
}

int	i_lessgreat(t_elem left, t_elem right)
{
	int fd1;

	fd1 = left.c ? *left.c - '0' : 0;
	if (open_on_fd(right.c, O_RDWR | O_CREAT, CREATE_RIGHTS, fd1) != -1)
		return (fd1);
	ft_printf("error : could not open %s\n", right.c);
	return (-1);
}

int	i_clobber(t_elem left, t_elem right)
{
	return(i_great(left, right));
}
