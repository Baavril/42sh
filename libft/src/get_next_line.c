/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 11:00:03 by tgouedar          #+#    #+#             */
/*   Updated: 2018/11/26 23:21:49 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void			ft_strappend(char **dest, char **src)
{
	char	*tmp;
	size_t	i;

	i = ft_strlen(*dest) + ft_strlen(*src) + 1;
	if (!(tmp = (char*)malloc(i)))
		return ;
	ft_memcpy(tmp, *dest, ft_strlen(*dest) + 1);
	tmp = ft_strcat(tmp, *src);
	ft_memdel((void**)dest);
	ft_memdel((void**)src);
	*dest = tmp;
}

static t_list_fd	*ft_lstfind_fd(t_list_fd **list, int fd)
{
	t_list_fd	*voyager;

	if (!(*list))
	{
		*list = (t_list_fd*)malloc(sizeof(t_list_fd));
		(*list)->fd = fd;
		(*list)->rd = NULL;
		(*list)->next = NULL;
	}
	voyager = *list;
	while ((voyager->fd - fd) && voyager->next)
		voyager = voyager->next;
	if ((voyager->fd - fd) && !(voyager->next))
	{
		voyager->next = (t_list_fd*)malloc(sizeof(t_list_fd));
		voyager = voyager->next;
		voyager->fd = fd;
		voyager->rd = NULL;
		voyager->next = NULL;
	}
	return (voyager);
}

static void			ft_lstfree(t_list_fd **cur, t_list_fd **stock)
{
	t_list_fd *voyager;

	voyager = *stock;
	if (*cur == voyager)
		*stock = (*stock)->next;
	else
	{
		while (voyager->next != *cur)
			voyager = voyager->next;
		voyager->next = (voyager->next)->next;
	}
	ft_memdel((void**)(&((*cur)->rd)));
	free(*cur);
}

static int			ft_read_fd(int fd, t_list_fd **cur, t_list_fd **stock)
{
	char	buf[BUFF_SIZE + 1];
	int		buf_read;

	(void)stock;
	if ((buf_read = read(fd, buf, BUFF_SIZE)) > 0)
	{
		free((*cur)->rd);
		buf[buf_read] = 0;
		(*cur)->rd = ft_strdup(buf);
		return (1);
	}
	ft_lstfree(cur, stock);
	return (buf_read);
}

int					get_next_line(const int fd, char **line)
{
	static t_list_fd	*stk = NULL;
	t_list_fd			*cur;
	char				*tmp;
	int					j;
	size_t				i;

	if (!line || fd < 0 || !(*line = ft_strnew(1)))
		return (-1);
	cur = ft_lstfind_fd(&stk, fd);
	if ((!(cur->rd) || !(*(cur->rd))) && ((j = ft_read_fd(fd, &cur, &stk)) < 1))
		return (j);
	while (((i = ft_strcspn(cur->rd, "\n")) || 1) && i == ft_strlen(cur->rd))
	{
		ft_strappend(line, &cur->rd);
		if ((j = ft_read_fd(fd, &cur, &stk)) < 1)
			break ;
	}
	if (cur->rd)
	{
		tmp = ft_strndup(cur->rd, i);
		ft_strappend(line, &tmp);
		if (cur->rd[i] == '\n')
			ft_memmove(cur->rd, cur->rd + i + 1, ft_strlen(cur->rd) - i);
	}
	return (1);
}
