/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2019/11/09 11:47:27 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell_variables.h"
#include "expansions.h"
#include "libft.h"

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
		if ((nb = ft_back_slashed(&(*tokens))) >= 0)
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
					if (g_symexp[j].expand(&(*tokens)) == ERROR)
					{
						ft_printf("42sh: %s: bad substitution\n", *tokens);
						return (NULL);
					}
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

int		expansions_treatment(char **tokens)
{
	char **splitok;

	if (!(splitok = ft_expsplit(*tokens, DOLLAR)))
		return (SUCCESS);
	free(*tokens);
	*tokens = expansions_management(splitok);
	return (SUCCESS);
}
