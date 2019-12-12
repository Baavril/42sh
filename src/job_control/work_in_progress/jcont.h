/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:18:20 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/12 00:38:07 by tgouedar         ###   ########.fr       */
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
# define ISRUNNING(status)		(status & RUNNING)
# define BACKGROUND				0x10000
# define FOREGROUND				0x0
# define ISBACKGROUND(status)	(status & BACKGROUND)
# define ISFOREGROUND(status)	!(ISBACKGROUND(status))
# define MAJOR_FAILLURE			0x40000

typedef struct		s_process
{
	pid_t			pid;
	int				status;
}					t_process;

typedef struct		s_job
{
	t_list			*process;
	pid_t			pgid;
	pid_t			controlling_pid;
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

/* ft_get_job.c */
int					ft_get_nbr_pgid(int nbr);
t_job				*ft_get_job_nbr(int job_nbr);
t_job				*ft_get_job_pgid(pid_t pgid);

/* ft_get_process_pid.c */
t_process			*ft_get_process_from_job(t_job *job, pid_t pid); // a passer en static ?
t_process			*ft_get_process_pid(pid_t pid);

void				ft_print_job(t_job *job, int opt);
void				ft_free_job(void *content, size_t size);
t_job				*ft_add_job(int status, char *cmd);
void				ft_set_prio(void);
int					ft_pop_job(int nbr);
void				ft_sigchld_handler(int nbr);
void				ft_update_job_status(void);



int			ft_add_process(void ft_exec(void), int std_fd[3], int fd_to_close[2]);
int			ft_launch_job(char *cmd, int status);

#endif
