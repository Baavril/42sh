/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_grammar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <tgouedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 15:50:39 by tgouedar          #+#    #+#             */
/*   Updated: 2020/05/27 16:41:19 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell_variables.h"
#include "libft.h"

extern struct s_svar	*g_svar;

char		*ft_getcwd(void)
{
	struct s_svar	*voyager;

	voyager = g_svar;
	while (voyager)
	{
		if (!(ft_strcmp(voyager->key, PWD)))
			return (voyager->value);
		voyager = voyager->next;
	}
	return ("");
}

char		*get_prompt_element(const char c)
{
	if (c == 'w')
		return (ft_getcwd());
	return ("");
}

size_t		replace_element(char **prompt, char *element, size_t j,
														const char *ps1)
{
	char		*tmp;
	size_t		el_len;

	el_len = ft_strlen(element);
	tmp = (char*)malloc(ft_strlen(ps1) + j + el_len + 1);
	ft_memcpy(tmp, *prompt, j);
	ft_memcpy(&(tmp[j]), element, el_len);
	ft_strdel(prompt);
	*prompt = tmp;
	return (el_len);
}

char		*mkprompt_expand(const char *ps1, size_t *len)
{
	char		*prompt;
	char		*element;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	prompt = (char*)malloc(ft_strlen(ps1) + 1);
	while (ps1[i])
	{
		if (ps1[i] == '\\')
		{
			element = get_prompt_element(ps1[++i]);
			j += replace_element(&prompt, element, j, &(ps1[++i]));
		}
		else
			prompt[j++] = ps1[i++];
	}
	prompt[j] = ps1[i];
	*len += ft_display_len(prompt);
	return (prompt);
}
