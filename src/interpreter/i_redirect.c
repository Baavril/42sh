/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:08:47 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/23 14:01:19 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>

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
	{
		return (open_on_fd(right.c,
				O_WRONLY | O_APPEND | O_CREAT, CREATE_RIGHTS, fd1));
	}
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
	return (i_great(left, right));
}
