/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:36:57 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/03 18:22:19 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"

t_job		*ft_new_job(int pgid, char *cmd)
{
	t_job	*new;

	if (!(new = (t_job*)malloc(sizeof(t_job))))
		return (NULL);
	
	return (new);
}
