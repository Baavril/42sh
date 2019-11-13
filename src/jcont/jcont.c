/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:12:16 by abarthel          #+#    #+#             */
/*   Updated: 2019/11/13 12:14:16 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "job.h"
#include "pipelines.h"


int	jcont(char **cmd, char **envp)
{
	char	**argv;
	int		ret;

	ret = 0;
	cmd = jump_sep(cmd);
	while (cmd && *cmd)
 	{
		argv = get_sequence(cmd);
		if (**argv)
		{
			ret = job(argv, envp);
		}
		ft_tabdel(&argv);
		cmd = position_token(cmd);
	}
	return (ret);
}

/*


pid_t				g_cur_gpid = 0;
t_list				*g_bg_jobs = NULL;

static int			ft_build_job(t_job *pipeline, char **cmd, size_t *i)
{
	size_t		pipe_start;
	size_t		pipe_end;

	if ((!ft_strcmp(cmd[*i], "&") || !ft_strcmp(cmd[*i], ";")) && !(cmd[*i + 1])) //& and ; are pipeline separator tokens that can be at the n of the line without syntax error
		return (0);
	pipe_start = (ft_ispipesepar(cmd[*i]) && (*i)) ? ++(*i) : *i; // replace ft_ispipesepar with the right function (written by abartel)
	pipe_end = pipe_start;
	while (cmd[pipe_end] && !ft_ispipesepar(cmd[pipe_end]))
		pipe_end++;
	*i = pipe_end;
	if (pipe_end == pipe_start)
	{
		//syntax error near cmd[pipe_end]
		return (-1); // cas d'un sep en debut ou de deux seps en suivant
	}
	//ft_memcheck(
	pipeline->command = ft_tab_range_cpy(cmd, pipe_start, pipe_end - 1);
	pipeline->process = NULL;
	// Comment set le groupe pid ?
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
    char        **pipe_av;
    t_process   process;
    size_t      i;

    i = 0;
    pipe_av = pipeline->command;
    while (pipe_av[i])
    {
        if (ft_issepar(pipe_av[i])) // function testing each command separator
        {
            //ft_memcheck(
		process.argv = ft_tab_range_cpy(pipe_av, 0, i);
            process.state = 0;
	        // Comment set le pid ?
            //ft_memcheck
		ft_lstaddback(&(pipeline->process), ft_lstnew(&process, sizeof(t_process)));
            pipe_av = &(pipe_av[i + 1]);
            i = 0;
        }
        else
            i++;
    }
    if (i)
    {
        //ft_memcheck(
	process.argv = ft_tab_range_cpy(pipe_av, 0, i);
        process.state = 0;
	   // Comment set le pid ?
        //ft_memcheck
	ft_lstaddback(&(pipeline->process), ft_lstnew(&process, sizeof(t_process)));
    }
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
    jobs = NULL;
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



*/
