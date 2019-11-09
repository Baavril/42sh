/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:12:45 by abarthel          #+#    #+#             */
/*   Updated: 2019/11/09 13:59:19 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JCONT_H
# define JCONT_H

# define COMPLETE			0x1
# define IFCOMPLETE(state)	(state & COMPLETE)
# define STOPPED			0x2
# define IFSTOPPED(state)	(state & STOPPED)



typedef struct				s_process
{
	struct s_proces			*next;       /* next process in pipeline */
	char					**argv;      /* for exec */
	pid_t					pid;         /* process ID */
	char					state;     /* true if process has stopped */
	int						ret_val;      /* reported status value */
}							t_process;

typedef struct				s_job
{
	struct s_job			*next;              /* next active job */
	char					*command;           /* command line, used for messages */
	t_process				*first_process;     /* list of processes in this job */
	pid_t					pgid;               /* process group ID */
	char					notified;           /* true if user told about stopped job */
	struct termios			tmodes;             /* saved terminal modes */
	int						fd_stdin;
	int						fd_stdout;
	int						fd_stderr;
}							t_job;

int							jcont(char **cmd, char **envp);

extern int					g_retval;

#endif
