/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_job.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 18:18:41 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/11 17:48:48 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"

void			ft_free_proc(void *content, size_t size)
{
	(void)size;
	free(content);
}

void			ft_free_job(void *content, size_t size)
{
	(void)size;
	free(((t_job*)content)->cmd);
	ft_lstdel(&(((t_job*)content)->process), &ft_free_proc);
	free(content);
}
