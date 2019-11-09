/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:12:45 by abarthel          #+#    #+#             */
/*   Updated: 2019/11/09 19:58:02 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JCONT_H
# define JCONT_H

# include 

# define COMPLETE			0x1
# define IFCOMPLETE(state)	(state & COMPLETE)
# define STOPPED			0x2
# define IFSTOPPED(state)	(state & STOPPED)



typedef struct				s_process
{
	char					**argv;      /* for exec */
	pid_t					pid;         /* process ID */
	char					state;     /* true if process has stopped */
//	t_ft_link				ft_to_link this process with the next
}							t_process;

typedef struct				s_job
{
	char					**command;           /* command line, used for messages */
	t_list					*process;     /* list of processes in this job */
//	pid_t					pgid;               /* process group ID */
	char					notified;           /* true if user told about stopped job */
//	struct termios			tmodes;             /* saved terminal modes */
	int						fd_stdin;
	int						fd_stdout;
	int						fd_stderr;
	int						ret_val;      /* reported status value */
}							t_job;

int							jcont(char **cmd, char **envp);

extern int					g_retval;

#endif
