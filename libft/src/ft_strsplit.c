/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:58:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/26 15:00:22 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	nb_words(const char *s, char c)
{
	size_t	i;
	size_t	p;
	size_t	words_nb;

	p = 0;
	i = 0;
	words_nb = 0;
	while (s[i])
	{
		p = 0;
		if (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			p++;
			i++;
		}
		if (p != 0)
			words_nb += 1;
	}
	return (words_nb);
}

static char		*mallnwrite(char const *s, size_t *l, char c)
{
	size_t	k;
	char	*string;

	k = 0;
	while (s[*l] == c && s[*l])
		++*l;
	while (s[*l + k] != c && s[*l + k] && s[*l])
		++k;
	string = (char*)malloc(sizeof(string) * k + 1);
	if (!string)
		return (NULL);
	string[k] = '\0';
	k = 0;
	while (s[*l + k] != c && s[*l + k] && s[*l])
	{
		string[k] = s[*l + k];
		++k;
	}
	*l += k;
	return (string);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	nb;
	size_t	index;
	size_t	l;
	char	**array;

	if (s)
		nb = nb_words(s, c);
	else
		return (NULL);
	array = (char**)malloc(sizeof(char*) * nb + 1);
	if (!array)
		return (NULL);
	array[nb] = 0;
	index = 0;
	l = 0;
	while (index < nb)
	{
		array[index] = mallnwrite(s, &l, c);
		++index;
	}
	return (array);
}
