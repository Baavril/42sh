/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shvar_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:43:12 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/08 18:19:18 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell_variables.h"
#include "maths_interne.h"
#include "libft.h"

//extern struct s_svar	*g_svar;

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
		listadd_back(newnodshell(assig_word, 0));
}
