/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_redirect_and.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 13:16:47 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/22 15:24:01 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "expansions.h"
#include <unistd.h>

int	i_lessand(t_elem *left, t_elem *right)
{
	int fd1;

	fd1 = left->c ? *left->c - '0' : 0;
	expansions_treatment(&right->c);
	if (*right->c == '-')
		close(fd1);
	else if (!right->c[1] && *right->c < '9' && *right->c >= '0'
			&& dup2(*right->c - '0', fd1) != -1)
		return (fd1);
	else if (!left->c && dup2(2, 1) != -1)
		return (open_on_fd(right->c, O_WRONLY | O_APPEND, 0, 1));
	else
		ft_printf("error : %s : incorrect fd\n", right->c);
	return (-1);
}

int	i_greatand(t_elem *left, t_elem *right)
{
	int fd1;

	fd1 = left->c ? *left->c - '0' : 1;
	expansions_treatment(&right->c);
	if (*right->c == '-')
		close(fd1);
	else if (!right->c[1] && *right->c < '9' && *right->c >= '0'
			&& dup2(*right->c - '0', fd1) != -1)
		return (fd1);
	else
		ft_printf("error : %s : incorrect fd\n", right->c);
	return (-1);
}
