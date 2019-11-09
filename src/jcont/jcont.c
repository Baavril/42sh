/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcont.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:59:39 by abarthel          #+#    #+#             */
/*   Updated: 2019/11/09 18:35:02 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "job.h"

pid_t				g_cur_gpid = 0;
t_list				*g_bg_jobs = NULL;

static char			**position_token(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && *(cmd[i]) == ';')
	{
		++i;
	}
	while (cmd[i] && *(cmd[i]) != ';')
	{
		++i;
	}
	while (cmd[i] && *(cmd[i]) == ';')
	{
		++i;
	}
	if (!(cmd[i]))
	{
		return (NULL);
	}
	return (&(cmd[i]));
}

static char			**jump_sep(char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i] && *(cmd[i]) == ';')
	{
		++i;
	}
	return (&cmd[i]);
}

static char			**ft_sequence(char **cmd)
{
	char **seq;
	int	i;

	i = 0;
	while (cmd[i] && *(cmd[i]) != ';')
	{
		++i;
	}
	seq = (char**)ft_tabmalloc(i + 1);
	i = 0;
	while (cmd[i] && *(cmd[i]) != ';')
	{
		seq[i] = ft_strdup(cmd[i]);
		++i;
	}
	return (seq);
}

static int			ft_build_job(t_job *pipeline, char **cmd, size_t *i)
{
	size_t		pipe_start;
	size_t		pipe_end;

	if (!ft_strcmp(cmd[*i], "&") && )
		return (0);
	pipe_start = (ft_ispipesepar(cmd[*i]) && (*i)) ? ++(*i) : *i;
	pipe_end = pipe_start;
	while (cmd[pipe_end] && !ft_ispipesepar(cmd[pipe_end]))
		pipe_end++;
	*i = pipe_end;
	if (pipe_end == pipe_start)
	{
		//syntax error near cmd[pipe_end]
		return (0); // cas d'un sep en debut ou de deux seps en suivant
	}
	pipeline->command = ft_tab_range_cpy(cmd, pipe_start, pipe_end - 1);
	pipeline->process = NULL;
	// Coment set le groupe pid ?
	pipeline->notified = !ft_strcmp(cmd[pipe_end], "&") ? 1 : 0;
	// Copy de term_mode;
	pipeline->fd_stdin = 0;
	pipeline->fd_stdout = 1;
	pipeline->fd_stderr = 2;
	pipeline->ret_val = -1;
	return (1);
}




int					jcont(char **cmd, char **envp)
{
	t_job	cur_job;
	char	**argv;
	int		ret;

	ret = 0;

	size_t		i;

	i = 0;
	while (i < ac && ft_build_job(&cur_job, cmd, &i))
	{
		ft_build_process(&cur_job, cmd, &i);
		ret = exec_pipeline(cur_job);
		if (IFCOMPLETE(ret))
			ft_reset_pipeline(&cur_job);
		else if (IFSTOPPED(ret))
			ft_lstadd(&g_bg_jobs, ft_lstnew(&cur_job, sizeof(t_job)));
	}





	cmd = jump_sep(cmd);




	while (cmd && *cmd)
	{
		argv = ft_sequence(cmd);
		if (**argv)
			ret = job(argv, envp);
		ft_tabdel(&argv);
		cmd = position_token(cmd);
	}
	return (ret);
}
