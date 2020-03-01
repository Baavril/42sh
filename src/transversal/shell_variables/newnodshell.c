/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newnodshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 11:37:47 by tgouedar          #+#    #+#             */
/*   Updated: 2020/03/01 11:41:08 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_variables.h"
#include "libft.h"

struct s_svar	*newnodshell(char *env, int exp)
{
	struct s_svar *svar_lst;

	svar_lst = NULL;
	if (*env)
	{
		if (!(svar_lst = (struct s_svar*)malloc(sizeof(struct s_svar))))
			return (NULL);
		svar_lst->str = ft_strdup(env);
		svar_lst->key = ft_strdupto(env, '=');
		svar_lst->value = ft_strdupfm(env, '=');
		svar_lst->exp = exp;
		svar_lst->next = NULL;
	}
	return (svar_lst);
}
