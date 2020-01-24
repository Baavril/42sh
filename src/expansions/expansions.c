/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/08 18:31:11 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell_variables.h"
#include "expansions.h"
#include "libft.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

t_symexp	g_symexp[] =
{
	{DIRECT_EXP, &direct_exp},
	{SIMPLE_EXP, &simple_exp},
	{WHY_EXP, &why_exp},
	{PLUS_EXP, &plus_exp},
	{DASH_EXP, &dash_exp},
	{EQUAL_EXP, &equal_exp},
	{BSHARP_EXP, &bsharp_exp},
	{OSHARP_EXP, &osharp_exp},
	{DSHARP_EXP, &osharp_exp},
	{OPERCENT_EXP, &opercent_exp},
	{DPERCENT_EXP, &opercent_exp},
	{MATHS_EXP, &maths_exp},
	{0, NULL}
};

static int		check_braces(char *token)
{
	int i;

	i = 0;
	if (token[i] == OP_BRACE)
	{
		while (token[i])
		{
			if (token[i] == CL_BRACE)
				return (SIMPLE_EXP);
			++i;
		}
	}
	return (DIRECT_EXP);
}

static int		check_colon(char *token)
{
	if (ft_strchr(token, COLON))
		return (COMPLEX_EXP);
	return (SIMPLE_EXP);
}

static int		check_symbol(char *token)
{
	int i;
	char *symbol;

	i = 1;
	symbol = NULL;
	if (token[i] == SHARP && ft_isprint(token[i + 1]))
		return (BSHARP_EXP);
	if ((symbol = ft_strchr(token, SHARP)))
	{
		if (symbol[1] == SHARP && ft_isprint(symbol[2]))
			return (DSHARP_EXP);
		return (OSHARP_EXP);
	}
	if ((symbol = ft_strchr(token, PERCENT)))
	{
		if (symbol[1] == PERCENT && ft_isprint(symbol[2]))
			return (DPERCENT_EXP);
		return (OPERCENT_EXP);
	}
	return (SIMPLE_EXP);
}

static int		check_colon_symbol(char *token)
{
	int i;

	i = 0;
	while (token[i] != COLON)
		++i;
	++i;
	if (token[i] == WHY)
		return (WHY_EXP);
	if (token[i] == PLUS)
		return (PLUS_EXP);
	if (token[i] == DASH)
		return (DASH_EXP);
	if (token[i] == EQUAL)
		return (EQUAL_EXP);
	return (SIMPLE_EXP);
}

static int		check_maths(char *token)
{
	int		i;
	int		opar;

	i = 2;
	opar = 0;
	if (!(token[0] == '(' && token[1] == '('))
		return (ERROR);
	while (token[i])
	{
		if (token[i] == '(')
			opar++;
		if ((token[i] == ')' && token[i + 1] == ')') && !opar)
			return (MATHS_EXP);
		if (token[i] == ')')
			opar--;
		if (opar < 0)
			return (ERROR);// parentheses imbriquees
		++i;
	}
	return (ERROR);
}

static int		identifier(char *token)
{
	if (*token == DOLLAR)
	{
		if (check_braces(token + 1) == SIMPLE_EXP)
		{
			if (check_colon(token + 1) == COMPLEX_EXP)
				return (check_colon_symbol(token + 1));
			return (check_symbol(token + 1));
		}
		else if (check_maths(token + 1) != ERROR)
			return (MATHS_EXP);
		return (DIRECT_EXP);
	}
	return (ERROR);
}

char	*ft_quoted(char *tokens)
{
	int c;
	int d;
	char *ret;

	c = 0;
	d = 0;
	ret = NULL;
	while (*tokens && *tokens != DQUOTES)
		tokens++;
	tokens++;
	while (*(tokens + c))
	{
		if (*(tokens + c) == DQUOTES)
			d++;
		c++;
	}
	if (c > d)
	{
		if (!(ret = (char*)ft_memalloc(sizeof(char) * (c - d + 1))))
			return (NULL);
	}
	else
	{
		if (!(ret = (char*)ft_memalloc(sizeof(char) * (d - c + 1))))
			return (NULL);
	}
	c = 0;
	d = 0;
	while (*(tokens + c))
	{
		if (*(tokens + c) == DQUOTES)
			c++;
		else
			ret[d++] = *(tokens + c++);
	}
	return (ret);
}

char	*ft_getbtw(char *tokens, int type)
{
	if (type == MATHS_EXP)
		return (ft_strdup(&(tokens[maths_len(tokens) + 2])));
	ft_printf("RET = %s\n", tokens);
	if (*tokens != DOLLAR)
		return (NULL);
	if (*tokens == DOLLAR && (*(tokens + 1) == SLASH
	|| *(tokens + 1) == SPC || !*(tokens + 1)))
		return (ft_strdup(tokens));
	if (ft_isin(DQUOTES, tokens))
		return (ft_quoted(tokens));
	while (*tokens && (*tokens == DOLLAR || *tokens == OP_BRACE))
		tokens++;
	while (type == DIRECT_EXP && *tokens && (ft_isalpha(*tokens) || ft_isdigit(*tokens)
	|| *tokens == AMPER || *tokens == UNDERSCORE))
		tokens++;
	while (type != DIRECT_EXP && *tokens && *tokens != CL_BRACE)
	{
		tokens++;
		if (*(tokens + 1) == AMPER)
			++tokens;
	}
	if (*tokens == CL_BRACE)
		++tokens;
	//if (*tokens == BSLASH)
	//	tokens++;
	ft_printf("RET = %s\n", tokens);
	return (ft_strdup(tokens));
}

int	ft_back_slashed(char **tokens)
{
	int i;
	int j;
	int ret;
	char *tmp;

	i = 0;
	j = 0;
	ret = 0;
	tmp = NULL;
	while (*((*tokens) + i) && *((*tokens) + i) == BSLASH)
		++i;
	j = i;
	if (j % 2)
	{
		j--;
		ret = -1;
	}
	j /= 2;
	if (j >= 0)
	{
		if (!ret)
		{
			tmp = ft_strdup((*tokens) + i);
			free(*tokens);
			*tokens = ft_strdup(tmp);
			free(tmp);
			ret = j;
		}
		else
		{
			tmp = ft_strdup((*tokens) + j + 1);
			free(*tokens);
			*tokens = ft_strdup(tmp);
			free(tmp);
		}
	}
	return (ret);
}

int		ft_setbslash(char **tokens, int nb)
{
	int i;
	char *tmp;

	if (!(tmp = (char*)ft_memalloc(sizeof(char) * (nb + 1))))
		return (0);
	i = 0;
	while (nb > 0)
	{
		*(tmp + i++) = BSLASH;
		--nb;
	}
	tmp = ft_strjoin(tmp, *tokens);
	free(*tokens);
	*tokens = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (SUCCESS);
}

char	*expansions_management(char **tokens)
{
	int j;
	int nb;
	int type;
	char *tmp;
	char *btw;

	j = 0;
	nb = 0;
	tmp = NULL;
	btw = NULL;
	while (*tokens)
	{
		j = 0;
		if ((nb = ft_back_slashed(tokens)) >= 0)
		{
			type = identifier(*tokens);
			ft_printf("type = %d\n", type);
			btw = ft_getbtw(*tokens, type);
			ft_printf("btw = %s\n", btw);
			ft_printf("token = %s\n", *tokens);
			while (g_symexp[j].expand)
			{
				if (g_symexp[j].sym == type)
				{
					if (g_symexp[j].expand(tokens) == ERROR)
					{
						ft_printf("42sh: %s: bad substitution\n", *tokens);
						return (NULL);
					}
					ft_printf("42sh: %s\n", *tokens);
				}
				++j;
			}
			if (nb > 0)
				ft_setbslash(&(*tokens), nb);
		}
		ft_printf("subtok = %s\n", *tokens);
		if (*tokens)
		{
			tmp = (tmp == NULL) ? ft_strdup(*tokens)
			: ft_strjoin(tmp, *tokens);
		}
		if (btw)
		{
			if (!**tokens && type == WHY_EXP)
				ft_strdel(&btw);
			else
			{
				tmp = (tmp == NULL) ? ft_strdup(btw)
				: ft_strjoin(tmp, btw);
				ft_strdel(&btw);
			}
		}
		++tokens;
	}
	return (tmp);
}

int		exp_limit(char *tokens)
{
	int i;

	i = 0;
	while (*tokens)
	{
		if (*tokens == BSLASH && *(tokens - 1) != BSLASH)
			i++;
		else if (*tokens == DOLLAR && *(tokens - 1) != BSLASH)
			i++;
		tokens++;
	}
	return (i);
}

char *malexps(char *str, int *len, char c)
{
	int r;
	int s;
	char *ret;

	r = 0;
	s = 0;
	while ((str[*len + r] == c || str[*len + r] == BSLASH) && str[*len])
		++r;
	while (!(str[*len + r] == c || str[*len + r] == BSLASH)
	&& str[*len + r] && str[*len])
		++r;
	if (!(ret = (char*)ft_memalloc(sizeof(char) * (r + 1))))
		return (NULL);
	r = 0;
	while ((str[*len + r] == c || str[*len + r] == BSLASH) && str[*len])
		ret[s++] = str[*len + r++];
	while (!(str[*len + r] == c || str[*len + r] == BSLASH)
	&& str[*len + r] && str[*len])
		ret[s++] = str[*len + r++];
	*len += r;
	return (ret);
}

char **ft_expsplit(char *str, char c)
{
	int i;
	int nb;
	int len;
	char **tab;

	i = 0;
	nb = exp_limit(str) + 1; /* nb +- 1 si '\' */
	if (nb == 0)
		return (NULL);
	if (!(tab = (char**)malloc(sizeof(char*) * (nb + 1))))
		return (NULL);
	len = 0;
	while (i < nb)
		tab[i++] = malexps(str, &len, c);
	tab[nb] = 0;
	return (tab);
}


char	**ft_globing(char **split)
{
	struct dirent *filedata;
	DIR *dirhandle;
	char **dir;
	char **tmp;
	char **ptm;
	int i;
	int j;
	int x;
	int n;

	i = 0;
	j = 0;
	n = 0;
	filedata = NULL;
	if (!(dir = (char **)malloc(sizeof(char *) * 4096)))
		return (NULL);
	while (split[i])
	{
		ft_printf("HEREEEEEEEEEEEEEEEEEE = %s\n", split[i]);
		if (!i)
		{
			if (!(dirhandle = opendir(".")))
			{
				ft_printf("readdir\n");
				return (NULL);
			}
			j = 0;
			while ((filedata = readdir(dirhandle)))
			{
				if (*(filedata->d_name) != '.')
				{
					dir[j] = ft_starmatch(filedata->d_name, split[i], 3);
					if (!*(dir[j]))
						free(dir[j]);
					else
						++j;
				}
			}
			dir[j] = 0;
		}
		else
		{
			j = 0;
			x = 0;
			tmp = ft_tabcpy(dir);
			while (tmp[j])
			{
				if ((dirhandle = opendir(tmp[j])))
				{
					while ((filedata = readdir(dirhandle)))
					{
						if (*(filedata->d_name) != '.')
						{
						ft_printf("see = %s\n", filedata->d_name);

							dir[x] = ft_strjoin(ft_strjoin(tmp[j], "/"), ft_starmatch(filedata->d_name, split[i], 3));
							if (!(dir[x][ft_strpchr(dir[x], '/') + 1]))
								free(dir[x]);
							else
								++x;
						}
					}
					dir[x] = 0;
				}
				++j;
			}
		}
		++i;
	}
	n = 0;
	ptm = (char**)malloc(sizeof(char*) * (ft_tablen(dir) + 1));
	while (dir[n])
	{
		ptm[n] = ft_strdup(dir[n]);
		++n;
	}
	ptm[n] = 0;
	closedir(dirhandle);
	return (ptm);
}

int		expansions_treatment(char **tokens)
{
//	int i;
//	char *tmp;
	char **splitok;
//	char **split;

/*	i = 0;
	ft_printf("matchexp = %s\n", *tokens);
	if (!(splitok = ft_expsplit(*tokens, DOLLAR)))
		return (SUCCESS);
	while (splitok[i])
	{
		ft_printf("split = %s\n", splitok[i]);
		i++;
	}*/
	/*
	if (**tokens == STAR || *(*tokens + 1) == STAR)
	{
		if (!(split = ft_strsplit(*tokens, "/")))
			return (ERROR);
		free(*tokens);
		*tokens = ft_globing(split);
	}
	*/
	if (!(splitok = ft_expsplit(*tokens, DOLLAR)))
		return (ERROR);
	free(*tokens);
	*tokens = expansions_management(splitok);
	return (SUCCESS);
}
