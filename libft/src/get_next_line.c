/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:01:41 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/07 14:17:05 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

#define CHR_SRCH '\n'

static __inline__ t_list	*lst_select(int fd)
{
	static t_list	*lst;
	t_list			*fd_lst;

	if (!lst)
		lst = ft_lstnew("", fd);
	fd_lst = lst;
	while ((int)(fd_lst->content_size) != fd)
	{
		if (!fd_lst->next)
		{
			fd_lst->next = ft_lstnew("", fd);
			return (fd_lst->next);
		}
		else if (fd_lst->next)
			fd_lst = fd_lst->next;
	}
	return (fd_lst);
}

static __inline__ int		feedline(t_list *lst, int ret, char **line, int has_chr)
{
	char	*location;
	char	*tmp;

	if (has_chr || (!ret && ft_isempty(lst->content)))
	{
		*line = ft_strsub(lst->content, 0, ft_strclen(lst->content, CHR_SRCH));
		if (!ret && ft_isempty(lst->content))
		{
			ft_strclr(lst->content);
			return (0);
		}
		tmp = lst->content;
		location = ft_strchr(lst->content, CHR_SRCH) + 1;
		lst->content = ft_strndup(location, ft_strlen(location));
		ft_memdel((void**)&tmp);
	}
	return (1);
}

static __inline__ int		readl(t_list *lst, int fd, char **line)
{
	int		ret;
	int		has_chr;
	char	buffer[BUFF_SIZE + 1];
	char	*tmp;

	ret = 1;
	while (!(has_chr = ft_chrsearch(lst->content, CHR_SRCH)))
	{
		ft_bzero(buffer, BUFF_SIZE + 1);
		if ((ret = read(fd, buffer, BUFF_SIZE)) < 0)
			return (-1);
		else if (!ret && !ft_isempty(lst->content))
			return (0);
		tmp = lst->content;
		lst->content = ft_strjoin(lst->content, buffer);
		ft_memdel((void**)&tmp);
		if (!ret)
			break ;
	}
	if (!(feedline(lst, ret, line, has_chr)))
		return (1);
	return (1);
}

int						get_next_line(const int fd, char **line)
{
	int		ret;
	int		isempty;
	t_list	*lst;

	lst = lst_select(fd);
	if (fd < 0 || !line || BUFF_SIZE < 0)
		return (-1);
	else if (!BUFF_SIZE || (!(ret = readl(lst, fd, line))
				&& !(isempty = ft_isempty(lst->content))))
		return (0);
	else
		return (ret);
}
