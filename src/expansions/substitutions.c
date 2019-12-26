/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitutions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2019/11/09 11:47:27 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

int		direct_exp(char **token)
{
	struct s_svar *tmp;

	tmp = g_svar;
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 1, (int)ft_strlen(g_svar->key) - 1) == 0
		&& !(ft_isalpha(token[0][(int)ft_strlen(g_svar->key)])
		|| ft_isdigit(token[0][(int)ft_strlen(g_svar->key)])
		|| token[0][(int)ft_strlen(g_svar->key)] == UNDERSCORE))
		{
			ft_strdel(token);
			*token = ft_strdup(g_svar->value);
			g_svar = tmp;
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	*token = ft_strdup(EMPTY_STR);
	g_svar = tmp;
	return (ERROR);
}

int		simple_exp(char **token)
{
	struct s_svar *tmp;

	tmp = g_svar;
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0)
		{
			ft_strdel(token);
			*token = ft_strdup(g_svar->value);
			g_svar = tmp;
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	*token = ft_strdup(EMPTY_STR);
	g_svar = tmp;
	return (ERROR);
}

char *ft_strcdup(char *token, char c)
{
	int i;
	char *ret;

	i = 0;
	ret = NULL;
	if (!token || !*token || *token == c)
		return (EMPTY_STR);
	while (token[i] != c)
		++i;
	if (!(ret = (char*)malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (token[i] != c)
	{
		ret[i] = token[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int		why_exp(char **token)
{
	char *var;
	char *word;
	struct s_svar *tmp;

	tmp = g_svar;
	word = ft_strcdup(ft_strchr(*token, WHY) + 1, CL_BRACE);
	var = ft_strcdup(*token + 2, COLON);
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0)
		{
			ft_strdel(token);
			if (g_svar->value)
				*token = ft_strdup(g_svar->value);
			else
			{
				*token = ft_strdup(EMPTY_STR);
				ft_printf("42sh : %s: %s\n", var, word);
			}
			ft_strdel(&var);
			ft_strdel(&word);
			g_svar = tmp;
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	*token = ft_strdup(EMPTY_STR);
	ft_printf("42sh : %s: %s\n", var, word);
	ft_strdel(&var);
	ft_strdel(&word);
	g_svar = tmp;
	return (ERROR);
}

int		plus_exp(char **token)
{
	struct s_svar *tmp;

	tmp = g_svar;
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0)
		{
			ft_strdel(token);
			if (g_svar->value)
				*token = ft_strdup(g_svar->value);
			else
				*token = ft_strdup(EMPTY_STR);
			g_svar = tmp;
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	*token = ft_strdup(EMPTY_STR);
	g_svar = tmp;
	return (ERROR);
}

int		dash_exp(char **token)
{
	char *keep;
	struct s_svar *tmp;

	tmp = g_svar;
	keep = ft_strcdup(ft_strchr(*token, DASH) + 1, CL_BRACE);
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0)
		{
			ft_strdel(token);
			if (g_svar->value)
				*token = ft_strdup(g_svar->value);
			else
				*token = keep;
			g_svar = tmp;
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	*token = keep;
	g_svar = tmp;
	return (ERROR);
}

char	*setasvar(char *token)
{
	char *ret;
	char *var;
	char *word;

	var = ft_strcdup(token + 2, COLON);
	word = ft_strcdup(ft_strchr(token, EQUAL), CL_BRACE);
	ret = ft_strjoin(var, word);
	ft_strdel(&word);
	ft_strdel(&var);
	return (ret);
}

int		equal_exp(char **token)
{
	char *keep;
	char *nod;
	struct s_svar *tmp;

	tmp = g_svar;
	nod = setasvar(*token);
	keep = ft_strchr(*token, EQUAL) + 1;
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0)
		{
			ft_strdel(token);
			if (g_svar->value)
				*token = ft_strdup(g_svar->value);
			else
			{
				*token = ft_strdup(keep);
				g_svar = tmp;
				if (checkvarlst(nod))
					listadd_back(newnodshell(nod, 0));
			}
			g_svar = tmp;
			cmd_set(0, NULL);
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	*token = ft_strndup(keep, ft_strlen(keep) - 1);
	g_svar = tmp;
	listadd_back(newnodshell(nod, 0));
	cmd_set(0, NULL);
	return (ERROR);
}

int		bsharp_exp(char **token)
{
	struct s_svar *tmp;

	tmp = g_svar;
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 3, ft_strlen(g_svar->key) - 1) == 0)
		{
			ft_strdel(token);
			*token = ft_itoa(ft_strlen(g_svar->value));
			g_svar = tmp;
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	g_svar = tmp;
	return (ERROR);
}

char *ft_alpharange(char c, char x)
{
	int i;
	int lim;
	char *ret;

	i = 0;
	ret = NULL;
	lim = (x - c) + 1;
	if (lim > 1)
	{
		if (!(ret = (char *)malloc(sizeof(char) * (lim + 1))))
			return (0);
		while (i < lim)
			ret[i++] = c++;
		ret[i] = '\0';
	}
	else
		ret = ft_strdup(EMPTY_STR);
	return (ret);
}

char	*ft_deploy(char *match)
{
	int		i;
	int		j;
	int		flag;
	int		dash;
	char	*keep;
	char	*range;

	i = 0;
	j = 0;
	flag = 0;
	dash = 0;
	keep = NULL;
	range = NULL;
	if (!(keep = (char*)malloc(sizeof(char) * (ft_strlen(match) + 1))))
		return(0);
	while (match[i] && match[i + 1])
	{
		flag = 0;
		if (match[i + 1] == DASH)
		{
			if (ft_isalpha(match[i]) && ft_isalpha(match[i + 2]))
			{
				range = (!dash) ? ft_alpharange(match[i], match[i + 2])
				: ft_strjoin(range, ft_alpharange(match[i], match[i + 2]));
				dash += 1;
				flag = 1;
				i += 2;
			}
		}
		if (!flag)
			keep[j++] = match[i];
		++i;
	}
	keep[j] = '\0';
	if (range)
		keep = ft_strjoin(keep, range);
	return (keep);
}

char	*ft_struchr(char *match, int len)
{
	int i;
	int j;
	char *ret;

	j = 0;
	i = 1;
	if (!(ret = (char*)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	ret[0] = match[1];
	while (match[i] && match[i] != CL_SQUAR)
	{
		j = 0;
		while (ret[j])
		{
			if ((ret[j] - match[i]) == 0)
				break;
			if (ret[j + 1] == '\0')
				ret[j + 1] = match[i];
			++j;
		}
		++i;
	}
	return (ret);
}

char	*ft_strneg(char *match)
{
	int i;
	int j;
	int c;
	char *strneg;
	char *strpos;

	i = 0;
	j = 0;
	c = 32;
	strpos = ft_struchr(match, ft_strlen(match));
	if (!(strneg = (char*)ft_memalloc(sizeof(char) * MAXCHR)))
		return (NULL);
	while (strpos[i] && c < 127)
	{
		if ((strpos[i] - c) == 0)
		{
			ft_printf("%c\n", strpos[i]);
			++i;
			++c;
		}
		else
			strneg[j++] = c++;
	}
	while (c < 127)
		strneg[j++] = c++;
	return (strneg);
}

int		ft_getbmatch(char *token, char *match, int flag)
{
	int i;
	int len;

	i = 0;
	len = (flag == OPERCENT_EXP) ? ft_strlen(token) - 1 : 0;
	if (ft_isin(DASH, match))
		match = ft_deploy(match);
	if (ft_isin(EXCLAM, match) || ft_isin(CARET, match))
		match = ft_strneg(match);
	while (match[i])
	{
		if (token[len] == match[i])
			return (SUCCESS);
		++i;
	}
	return (ERROR);
}

char *ft_strwhy(char *token, char *match, int flag)
{
	int i;
	int len;
	int lim;
	char *ret;

	i = 0;
	lim = 0;
	ret = NULL;
	if ((len = (int)ft_strlen(token) - (int)ft_strlen(match)) <= 0)
		return (ft_strdup(EMPTY_STR));
	if (flag == OPERCENT_EXP)
	{
		if (len > 0)
			return (ret = ft_strndup(token, len));
	}
	if (len > 0)
	{
		if (!(ret = (char*)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		lim = ft_strlen(match);
	}
	else
		return (token);
	while (i < len)
		ret[i++] = token[lim++];
	ret[i] = '\0';
	return (ret);
}

int	ft_strpchr(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] - c == 0)
			return (i);
		i++;
	}
	return (0);
}

char	*ft_strmatch(char *token, char *match, char flag)
{
	int len;
	char *ret;

	ret = NULL;
	len = ft_strlen(match);
	if (ft_isin(STAR, match))
		ret = (flag == 2) ? ft_strdup(EMPTY_STR)
		: ft_strdup(token);
	else if (ft_strncmp(token, match, len) == 0)
		ret = ft_strdupfm(token, match[len - 1]);
	else if (match[ft_strpchr(match, WHY)] == WHY)
		ret = ft_strwhy(token, &match[ft_strpchr(match, WHY)], OSHARP_EXP);
	else if (len > 1 && *match == OP_SQUAR
	&& ft_getbmatch(token, match + 1, OSHARP_EXP) == SUCCESS)
		ret = ft_strdup(&token[1]);
	else
		ret = ft_strdup(token);
	return (ret);
}

int ft_spechrlen(char *token)
{
	int pos;

	if ((pos = ft_strpchr(token, SHARP)))
		return ((token[pos + 1] == SHARP)
		? SUCCESS : ERROR);
	if ((pos = ft_strpchr(token, PERCENT)))
		return ((token[pos + 1] == PERCENT)
		? SUCCESS : ERROR);
	return (ERROR);
}

int		osharp_exp(char **token)
{
	int flag;
	char *word;
	struct s_svar *tmp;

	tmp = g_svar;
	flag = (!(ft_spechrlen(*token))) ? 2 : 1;
	word = ft_strcdup(ft_strchr(*token, SHARP) + flag, CL_BRACE);
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0)
		{
			ft_strdel(token);
			*token = ft_strmatch(g_svar->value, word, flag);
			g_svar = tmp;
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	*token = ft_strdup(EMPTY_STR);
	g_svar = tmp;
	return (ERROR);
}

int ft_strlncmp(const char *s1, const char *s2, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (s1[i])
		++i;
	--i;
	while (s2[j])
		++j;
	--j;
	while (len > 0 && s1[i] && s2[j] && s1[i] == s2[j])
	{
	ft_printf("%c\n", s1[i]);
	ft_printf("%c\n", s2[j]);
		--len;
		--i;
		--j;
	}
	if (!len)
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

char	*ft_strpmatch(char *token, char *match, char flag)
{
	int len;
	char *ret;

	ret = NULL;
	len = ft_strlen(match);
	if (ft_isin(STAR, match))
		ret = (flag == 2) ? ft_strdup(EMPTY_STR)
		: ft_strdup(token);
	else if (ft_strlncmp(token, match, len) == 0)
		ret = ft_strndup(token, ft_strlen(token) - ft_strlen(match));
	else if (match[ft_strpchr(match, WHY)] == WHY)
		ret = ft_strwhy(token, &match[ft_strpchr(match, WHY)], OPERCENT_EXP);
	else if (len > 1 && *match == OP_SQUAR
	&& ft_getbmatch(token, match + 1, OPERCENT_EXP) == SUCCESS)
		ret = ft_strndup(token, ft_strlen(token) - 1);
	else
		ret = ft_strdup(token);
	return (ret);
}

int		opercent_exp(char **token)
{
	int flag;
	char *word;
	struct s_svar *tmp;

	tmp = g_svar;
	flag = (!(ft_spechrlen(*token))) ? 2 : 1;
	word = ft_strcdup(ft_strchr(*token, PERCENT) + flag, CL_BRACE);
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0)
		{
			ft_strdel(token);
			*token = ft_strpmatch(g_svar->value, word, flag);
			g_svar = tmp;
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	*token = ft_strdup(EMPTY_STR);
	g_svar = tmp;
	return (ERROR);
}
