/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_redirect_and.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 13:16:47 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/29 15:42:24 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <unistd.h>

int	i_lessand(t_elem left, t_elem right)
{
	int fd1;

	fd1 = left.c ? *left.c - '0' : 0;
	if (!*right.c)
		ft_dprintf(STDERR_FILENO, "42sh: %s: Redirection ambigue\n", right.c);
	else if (dup2(*right.c - '0', fd1) != -1)
		return (fd1);
	ft_dprintf(STDERR_FILENO, "42sh: %s: incorrect fd\n", right.c);
	return (-1);
}

int	i_greatand(t_elem left, t_elem right)
{
	int fd1;

	fd1 = left.c ? *left.c - '0' : 1;
	if (!*right.c)
		ft_dprintf(STDERR_FILENO, "42sh: %s: Redirection ambigue\n", right.c);
	else if (dup2(*right.c - '0', fd1) != -1)
		return (fd1);
	ft_dprintf(STDERR_FILENO, "42sh: %s: incorrect fd\n", right.c);
	return (-1);
}

int	i_andgreat(t_elem left, t_elem right)
{
	int rtn;

	left.c = ft_strdup("1");
	rtn = i_great(left, right);
	if (rtn > 0)
	{
		*left.c = '2';
		rtn = i_great(left, right);
	}
	ft_strdel(&left.c);
	return(rtn);
}
