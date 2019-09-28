/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_whitespaces.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 12:58:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/27 18:04:26 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	count_words(char *str, char *whitespaces)
{
	char	*cpy;
	int		nb;

	nb = 0;
	if (!(cpy = ft_strdup(str)))
		return (-1);
	if (ft_strtok(cpy, whitespaces))
		++nb;
	else
	{
		ft_memdel((void**)&cpy);
		return (nb);
	}
	while (ft_strtok(NULL, whitespaces))
		++nb;
	ft_memdel((void**)&cpy);
	return (nb);
}

static int	get_tokens(char **str, char *whitespaces, char **tokens)
{
	char	*tok;
	char	*pstr;
	int		nb;

	nb = 0;
	pstr = *str;
	while ((tok = ft_strtok(pstr, whitespaces)))
	{
		if (!nb && !tok)
		{
			ft_tabdel(&tokens);
			ft_memdel((void**)str);
			return (-1);
		}
		if (!(tokens[nb] = ft_strdup(tok)))
		{
			ft_tabdel(&tokens);
			return (-1);
		}
		pstr = NULL;
		++nb;
	}
	return (0);
}

static int	copy_tab(char *str, char *whitespaces, char **tokens)
{
	char	*cpy;

	if (!(cpy = ft_strdup(str)))
	{
		ft_tabdel(&tokens);
		return (-1);
	}
	if (get_tokens(&cpy, whitespaces, tokens) == -1)
		return (-1);
	ft_memdel((void**)&cpy);
	return (0);
}

char		**ft_strsplit_whitespaces(char *str)
{
	char	**tokens;
	char	*whitespaces;
	int		nb_words;

	whitespaces = " \t\n\v\f\r";
	if ((nb_words = count_words(str, whitespaces)) <= 0
		|| !(tokens = (char**)ft_tabmalloc(nb_words + 1))
		|| copy_tab(str, whitespaces, tokens) == -1)
		return (NULL);
	return (tokens);
}
