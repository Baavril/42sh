/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_open_on_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 13:20:56 by bprunevi          #+#    #+#             */
/*   Updated: 2020/01/04 16:38:51 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

int	open_on_fd(const char *path, int o_flags, mode_t mode, int final_fd)
{
	int open_fd;

	if ((open_fd = open(path, o_flags, mode)) != -1)
	{
		dup2(open_fd, final_fd);
		close(open_fd);
		return (final_fd);
	}
	return (-1);
}
