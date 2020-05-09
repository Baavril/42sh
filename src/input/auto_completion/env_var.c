/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <yberramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 23:34:34 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/09 23:45:15 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

extern struct s_svar	*g_svar;

static char		*ft_dollar_brace(char *str)
{
	int		i;
	int		y;
	char	*tmp;

	i = 0;
	y = 0;
	if (!(tmp = (char*)malloc(sizeof(char) * (ft_strlen(str) + 3))))
		return (NULL);
	tmp[0] = '$';
	tmp[1] = '{';
	y += 2;
	while (str[i + 1] != '\0')
	{
		tmp[y] = str[i];
		i++;
		y++;
	}
	tmp[y] = '}';
	y++;
	tmp[y] = '\0';
	return (tmp);
}

static char		*ft_dollar(char *str)
{
	char	*tmp;
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (!(tmp = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	tmp[y] = '$';
	y++;
	while (str[i + 1] != '\0')
	{
		tmp[y] = str[i];
		i++;
		y++;
	}
	tmp[y] = '\0';
	return (tmp);
}

static char		*ft_assign_words(char *str, int dollar)
{
	char	*tmp;

	if (dollar == 1)
	{
		if (!(tmp = ft_dollar(str)))
			return (NULL);
	}
	else if (!(tmp = ft_dollar_brace(str)))
		return (NULL);
	return (tmp);
}

static int		ft_cmp_str(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 && !str2)
		return (0);
	while (str1[i] && str2[i] && !ft_isspace(str1[i]))
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str1[i] && str2 && !ft_isspace(str1[i]))
		return (0);
	return (1);
}

int				ft_env_var(char *input, int dollar, char ***words)
{
	int				i;
	int				y;
	struct s_svar	*tmp;
	struct s_svar	*tmp2;

	i = 0;
	y = 0;
	tmp = g_svar;
	tmp2 = g_svar;
	while (tmp2)
	{
		if (ft_cmp_str(input, tmp2->key))
			i++;
		tmp2 = tmp2->next;
	}
	if (i == 0)
	{
		(*words) = NULL;
		return (1);
	}
	if (!((*words) = (char**)malloc(sizeof(char*) * (i + 1))))
	{
		(*words) = NULL;
		return (0);
	}
	while (tmp)
	{
		if (ft_cmp_str(input, tmp->key))
		{
			if (!((*words)[y] = ft_assign_words(tmp->key, dollar)))
			{
				(*words) = NULL;
				del_double_char((*words));
				return (0);
			}
			y++;
			(*words)[y] = NULL;
		}
		tmp = tmp->next;
	}
	return (1);
}
