/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_redirect_and.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 13:16:47 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/21 12:51:07 by bprunevi         ###   ########.fr       */
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
	if (dup2(*right->c - '0', fd1) != -1)
		return (fd1);
	ft_printf("error : %s : incorrect fd\n", right->c);
	return (-1);
}

int	i_greatand(t_elem *left, t_elem *right)
{
	int fd1;

	fd1 = left->c ? *left->c - '0' : 1;
	expansions_treatment(&right->c);
	if (dup2(*right->c - '0', fd1) != -1)
		return (fd1);
	ft_printf("error : %s : incorrect fd\n", right->c);
	return (-1);
}
