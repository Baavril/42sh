/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:18:20 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/07 18:14:21 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JCONT_H
# define JCONT_H

# include <stdlib.h>
# include "libft.h"

# define MAX_STATE_LEN			23
# define JOBS_OPT				"+lp"
# define L_OPT					1
# define P_OPT					2

# define RUNNING				0x20000
# define ISRUNNING(status)		(status & RUNNING) && 
# define BACKGROUND				0x10000
# define FOREGROUND				0x0
# define ISBACKGROUND(status)	(status & BACKGROUND)
# define ISFOREGROUND(status)	!(ISBACKGROUND(status))

typedef struct		s_job
{
	pid_t			pgid;
	int				status;
	char			*cmd;
	int				nbr;
}					t_job;

typedef struct		s_jcont
{
	t_list			*jobs;
	size_t			job_nbr;
	size_t			active_jobs[2];
}					t_jcont;

void				ft_print_job(t_job *job);
void				ft_free_job(void *content, size_t size);
int					ft_add_job(pid_t pgid, char *cmd);
void				ft_set_prio(void);

#endif
