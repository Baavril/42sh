/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_job.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 18:18:41 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/05 12:05:07 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"

static void		ft_free_proc(void *content, size_t size)
{
	(void)size;
	free(content);
}

void	ft_free_job(void *content, size_t size)
{
	(void)size;
	free(((t_job*)content)->cmd);
	ft_lstdel(&(((t_job*)content)->process), &ft_free_proc);
	free(content);
}
