/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shvar_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:43:12 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/22 14:50:49 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell_variables.h"
#include "maths_expansion.h"
#include "libft.h"

extern struct s_svar	*g_svar;

int						ft_is_varname(const char *token)
{
	if (ft_isdigit(*token))
		return (0);
	while (*token)
	{
		if (!(ft_isalnum(*token) || *token == '_'))
			return (0);
		token++;
	}
	return (1);
}

char					*getshvar(char *var_name)
{
	struct s_svar	*tmp;
	char			*var_value;

	var_value = NULL;
	tmp = g_svar;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, var_name, ft_strlen(tmp->key) - 1))
		{
			var_value = ft_strdup(tmp->value); // ft_memcheck ?
			break ;
		}
		tmp = tmp->next;
	}
	if (!var_value)
		return (ft_strdup("0")); // ft_memcheck ?
	return (var_value);
}

void					setshvar(char *var_name, int64_t value)
{
	char	*assig_word;
	char	*var_value;
	size_t	name_len;
	size_t	val_len;

	if (!var_name)
		return ;
	var_value = ft_itoa64(value);
	name_len = ft_strlen(var_name);
	val_len = ft_strlen(var_value);
	assig_word = (char*)malloc(name_len + val_len + 2); // ft_memcheck ?
	ft_memcpy(assig_word, var_name, name_len);
	assig_word[name_len] = '=';
	ft_memcpy(assig_word + name_len + 1, var_value, val_len);
	assig_word[name_len + 1 + val_len] = '\0';
	if (checkvarlst(assig_word))
		setenvnod(newnodshell(assig_word, 0));
	ft_strdel(&assig_word);
	ft_strdel(&var_value);
}
