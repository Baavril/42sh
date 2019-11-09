/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:59:39 by abarthel          #+#    #+#             */
/*   Updated: 2019/11/09 21:07:29 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "job.h"

pid_t				g_cur_gpid = 0;
t_list				*g_bg_jobs = NULL;

static int			ft_build_job(t_job *pipeline, char **cmd, size_t *i)
{
	size_t		pipe_start;
	size_t		pipe_end;

	if ((!ft_strcmp(cmd[*i], "&") || !ft_strcmp(cmd[*i], ";")) && !(cmd[*i + 1]))
		return (0);
	pipe_start = (ft_ispipesepar(cmd[*i]) && (*i)) ? ++(*i) : *i;
	pipe_end = pipe_start;
	while (cmd[pipe_end] && !ft_ispipesepar(cmd[pipe_end]))
		pipe_end++;
	*i = pipe_end;
	if (pipe_end == pipe_start)
	{
		//syntax error near cmd[pipe_end]
		return (-1); // cas d'un sep en debut ou de deux seps en suivant
	}
	/*ft_memcheck(*/pipeline->command = ft_tab_range_cpy(cmd, pipe_start, pipe_end - 1);
	pipeline->process = NULL;
	// Coment set le groupe pid ?
	pipeline->notified = !ft_strcmp(cmd[pipe_end], "&") ? 1 : 0;
	// Copy de term_mode;
	pipeline->fd_stdin = 0;
	pipeline->fd_stdout = 1;
	pipeline->fd_stderr = 2;
	pipeline->ret_val = -1; //?
	return ((command[pipe_end])); //1: means there are more jobs to come ; 0: all arg in a pipeline
}

static void			ft_build_process(t_job *pipeline)
{


}

static int			ft_exec_pipeline(t_job *pipeline)
{
	
}

static void			ft_exec_jobs(t_list **jobs)
{
	t_list		*voyager;

	voyager = *jobs;
	ret = ft_exec_pipeline((t_job*)(voyager->content));
	if (IFSTOPPED(ret))
	{
		ft_lstadd(&g_bg_voyager, voyager);
		*jobs = (*jobs)->next;
	}
	while (voyager->next)
	{
		ret = ft_exec_pipeline((t_job*)((voyager->next)->content));
		if (IFSTOPPED(ret))
		{
			ft_lstadd(&g_bg_voyager, voyager->next);
			voyager->next = (voyager->next)->next;
		}
		voyager = voyager->next;
	}
}

int					jcont(char **cmd, char **envp)
{
	t_job		pipeline;
	t_list		*jobs;
	size_t		i;
	int			ret;

	i = 0;
	while ((ret = ft_build_job(&pipeline, cmd, &i)) > 0)
	{
		ft_build_process(&pipeline);
		ft_lstaddback(&jobs, ft_lstnew(pipeline, sizeof(t_job)));
	}
	if (ret == 0)
		ft_exec_jobs(&jobs);
	ft_lstdel(&jobs, &ft_free_job);
	return (ret);
}
