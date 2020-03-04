/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_substitutions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunev           #+#    #+#             */
/*   Updated: 2020/03/01 11:45:18 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell_variables.h"
#include "builtin_test.h"
#include "expansions.h"
#include "libft.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

static int		tilde_int_exp(char **token, char *end, int flag)
{
	char	*tmp;

	tmp = NULL;
	if ((flag == 2 || flag == 3) && *(*token + flag - 1) == '0')
	{
		tmp = ft_getenv("PWD");
		ft_strdel(token);
		*token = ft_strjoin(tmp, end);
		ft_strdel(&tmp);
		return (SUCCESS);
	}
	return (ERROR);
}

static int		tilde_nude_exp(char **token, char *end, int flag)
{
	char	*tmp;

	tmp = NULL;
	if (flag == 1 && (*(*token + flag) == SLASH || !(*(*token + flag))))
	{
		tmp = ft_getenv("HOME");
		ft_strdel(token);
		*token = ft_strjoin(tmp, end);
		ft_strdel(&tmp);
		return (SUCCESS);
	}
	return (ERROR);
}

static int		tilde_minus_exp(char **token, char *end)
{
	char	*tmp;

	tmp = NULL;
	if (*(*token + 1) == MINUS && (*(*token + 2) == SLASH || !(*(*token + 2))))
	{
		tmp = ft_getenv("OLDPWD");
		ft_strdel(token);
		*token = ft_strjoin(tmp, end);
		ft_strdel(&tmp);
		return (SUCCESS);
	}
	return (ERROR);
}

static int		tilde_plus_exp(char **token, char *end)
{
	char	*tmp;

	tmp = NULL;
	if (*(*token + 1) == PLUS && (*(*token + 2) == SLASH || !(*(*token + 2))))
	{
		tmp = ft_getenv("PWD");
		ft_strdel(token);
		*token = ft_strjoin(tmp, end);
		ft_strdel(&tmp);
		return (SUCCESS);
	}
	return (ERROR);
}

int				tilde_exp(char **token)
{
	char	*end;
	char	*user;
	int		flag;

	flag = 1;
	user = ft_getenv("USER");
	if ((*token)[ft_strpchr(*token, TILDE) + 1] == PLUS
	|| (*token)[ft_strpchr(*token, TILDE) + 1] == MINUS)
		flag += 1;
	if (*(*token + flag) == '0')
		flag += 1;
	else if (ft_strncmp(user, *token + 1, ft_strlen(user)) == 0)
		flag += ft_strlen(user);
	end = ft_strdup(&(*token)[ft_strpchr(*token, TILDE) + flag]);
	tilde_plus_exp(token, end);
	tilde_minus_exp(token, end);
	tilde_nude_exp(token, end, flag);
	tilde_int_exp(token, end, flag);
	ft_strdel(&end);
	ft_strdel(&user);
	return (SUCCESS);
}
