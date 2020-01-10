/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitutions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/08 13:58:54 by tgouedar         ###   ########.fr       */
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
	return (SUCCESS);
}

int		simple_exp(char **token)
{
	struct s_svar *tmp;

	tmp = g_svar;
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0
				&& !(ft_isalpha(token[0][(int)ft_strlen(g_svar->key) + 1])
					|| ft_isdigit(token[0][(int)ft_strlen(g_svar->key) + 1])
					|| token[0][(int)ft_strlen(g_svar->key) + 1] == UNDERSCORE))
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
	return (SUCCESS);
}

char *ft_strcdup(char *token, char c)
{
	int i;
	char *ret;

	i = 0;
	ret = NULL;
	if (!token || !*token || *token == c)
		return (NULL);
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
	if (!(var = ft_strcdup(*token + 2, COLON)))
		return (ERROR);
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0
				&& !(ft_isalpha(token[0][(int)ft_strlen(g_svar->key) + 1])
					|| ft_isdigit(token[0][(int)ft_strlen(g_svar->key) + 1])
					|| token[0][(int)ft_strlen(g_svar->key) + 1] == UNDERSCORE))
		{
			ft_strdel(token);
			if (g_svar->value && *(g_svar->value))
				*token = ft_strdup(g_svar->value);
			else
			{
				*token = ft_strdup(EMPTY_STR);
				(word) ? ft_printf("42sh : %s: %s\n", var, word)
					: ft_printf("42sh : %s: parameter null\n", var);
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
	(word) ? ft_printf("42sh : %s: %s\n", var, word)
		: ft_printf("42sh : %s: parameter not set\n", var);
	ft_strdel(&var);
	ft_strdel(&word);
	g_svar = tmp;
	return (SUCCESS);
}

int		plus_exp(char **token)
{
	char	*var;
	char	*keep;
	struct	s_svar *tmp;

	tmp = g_svar;
	if (!(var = ft_strcdup(*token + 2, COLON)))
		return (ERROR);
	keep = ft_strcdup(ft_strchr(*token, PLUS) + 1, CL_BRACE);
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0
				&& !(ft_isalpha(token[0][(int)ft_strlen(g_svar->key) + 1])
					|| ft_isdigit(token[0][(int)ft_strlen(g_svar->key) + 1])
					|| token[0][(int)ft_strlen(g_svar->key) + 1] == UNDERSCORE))
		{
			ft_strdel(token);
			if (g_svar->value && *(g_svar->value) && keep && *keep)
				*token = ft_strdup(keep);
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
	return (SUCCESS);
}

int		dash_exp(char **token)
{
	char *var;
	char *keep;
	struct s_svar *tmp;

	tmp = g_svar;
	if (!(var = ft_strcdup(*token + 2, COLON)))
		return (ERROR);
	keep = ft_strcdup(ft_strchr(*token, DASH) + 1, CL_BRACE);
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0
				&& !(ft_isalpha(token[0][(int)ft_strlen(g_svar->key) + 1])
					|| ft_isdigit(token[0][(int)ft_strlen(g_svar->key) + 1])
					|| token[0][(int)ft_strlen(g_svar->key) + 1] == UNDERSCORE))
		{
			ft_strdel(token);
			if (g_svar->value && *(g_svar->value))
				*token = ft_strdup(g_svar->value);
			else
				*token = (keep && *keep) ? ft_strdup(keep) : ft_strdup(EMPTY_STR);
			g_svar = tmp;
			ft_strdel(&keep);
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	*token = (keep && *keep) ? ft_strdup(keep) : ft_strdup(EMPTY_STR);
	g_svar = tmp;
	ft_strdel(&keep);
	return (SUCCESS);
}

char	*setasvar(char *token)
{
	char *ret;
	char *var;
	char *word;

	if (!(var = ft_strcdup(token + 2, COLON)))
		return (NULL);
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
	if (!(nod = setasvar(*token)))
		return (ERROR);
	keep = ft_strcdup(ft_strchr(*token, EQUAL) + 1, CL_BRACE);
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0
				&& !(ft_isalpha(token[0][(int)ft_strlen(g_svar->key) + 1])
					|| ft_isdigit(token[0][(int)ft_strlen(g_svar->key) + 1])
					|| token[0][(int)ft_strlen(g_svar->key) + 1] == UNDERSCORE))
		{
			free(*token);
			if (g_svar->value && *(g_svar->value))
				*token = ft_strdup(g_svar->value);
			else
			{
				*token = (keep && *keep) ? ft_strdup(keep) : ft_strdup(EMPTY_STR);
				g_svar = tmp;
				if (checkvarlst(nod))
					listadd_back(newnodshell(nod, 0));
			}
			g_svar = tmp;
			ft_strdel(&keep);
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	free(*token);
	*token = (keep && *keep) ? ft_strdup(keep) : ft_strdup(EMPTY_STR);
	ft_strdel(&keep);
	g_svar = tmp;
	listadd_back(newnodshell(nod, 0));
	return (SUCCESS);
}

/* still need to fix the management of positional parameters and arrays. see bash man p 28 */

int		bsharp_exp(char **token)
{
	struct s_svar *tmp;

	tmp = g_svar;
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 3, ft_strlen(g_svar->key) - 1) == 0
				&& !(ft_isalpha(token[0][(int)ft_strlen(g_svar->key) + 2])
					|| ft_isdigit(token[0][(int)ft_strlen(g_svar->key) + 2])
					|| token[0][(int)ft_strlen(g_svar->key) + 2] == UNDERSCORE))
		{
			ft_strdel(token);
			*token = ft_itoa(ft_strlen(g_svar->value));
			g_svar = tmp;
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	g_svar = tmp;
	ft_strdel(token);
	*token = ft_itoa(0);
	return (SUCCESS);
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
//	else
//		ret = ft_strdup(EMPTY_STR);
	return (ret);
}

char	*ft_deploy(char *match)
{
	int		i;
	int		j;
	int		flag;
	int		dash;
	char	*keep;
	char	*tmp;
	char	*ptm;
	char	*range;

	i = 0;
	j = 0;
	flag = 0;
	dash = 0;
	tmp = NULL;
	keep = NULL;
	ptm = NULL;
	range = NULL;
	if (!(keep = (char*)malloc(sizeof(char) * (ft_strlen(match)))))
		return(0);
	while (match[i] && match[i + 1])
	{
		flag = 0;
		if (match[i + 1] == DASH)
		{
			if (ft_isalpha(match[i]) && ft_isalpha(match[i + 2]))
			{
				if (!dash)
					range = ft_alpharange(match[i], match[i + 2]);
				else
				{
					tmp = ft_alpharange(match[i], match[i + 2]);
					ptm = range;
					range = ft_strjoin(ptm, tmp);
					ft_strdel(&tmp);
					ft_strdel(&ptm);
					}

			//	range = (!dash) ? ft_alpharange(match[i], match[i + 2]) : ft_strjoin(range, ft_alpharange(match[i], match[i + 2]));
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
	{
		tmp = keep;
		keep = ft_strjoin(tmp, range);
		ft_strdel(&tmp);
		ft_strdel(&range);
	}
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

int		ft_getdeploy(char **match)
{
	char *tmp;

	tmp = NULL;
	if (ft_isin(DASH, *match))
	{
		tmp = *match;
		*match = ft_deploy(tmp);
		ft_strdel(&tmp);
	}
	if (ft_isin(EXCLAM, *match) || ft_isin(CARET, *match))
	{
		tmp = *match;
		*match = ft_strneg(tmp);
		ft_strdel(&tmp);
	}
	return (SUCCESS);
}

int		ft_getbmatch(char *token, char *match, int flag)
{
	int i;
	int len;

	i = 0;
	len = (flag == OPERCENT_EXP) ? ft_strlen(token) - 1 : 0;
	ft_getdeploy(&match);
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

int		ft_checkdeploy(char *str, char *match, int flag, int star)
{
	char *tmp;
	char *ptm;
	char c;
	char ret;
	int i;

	i = 0;
	c = 0;
	ret = 0;
	ptm = NULL;
	tmp = NULL;
	if (star && (match[i] == CARET || match[i + 1] == CARET))
	{
		ptm = ft_strdupto(match + (ft_strpchr(match, CARET) + 1), CL_SQUAR);
		ft_getdeploy(&ptm); /*voir si ca casse rien */
	}
	if (match[i] == OP_SQUAR)
	{
		tmp = ft_strdupto(match + (ft_strpchr(match, OP_SQUAR) + 1), CL_SQUAR);
		ft_getdeploy(&tmp);
	}
	if ((int)ft_strlen(str) <= 0)
	{
		ft_strdel(&ptm);
		ft_strdel(&tmp);
		return (ret);
	}
	while (ptm && ptm[i])
	{
		if (ptm[i] == *str)
		{
			++str;
			i = -1;
		}
		++i;
	}
	while (tmp[i] && ft_strlen(str) > 0)
	{
		if (tmp[i] == *str && flag == 1)
		{
			while (c != tmp[i])
				c++;
			ft_strdel(&ptm);
			ft_strdel(&tmp);
			return (c);
		}
		else if (tmp[i] == *str && flag >= 2)
		{
			str++;
			c = tmp[i];
			i = -1;
			ret++;
		}
		++i;
	}
	ft_strdel(&tmp);
	ft_strdel(&ptm);
	return ((ret) ? c : ERROR);
}

char *ft_starmatch(char *str, char *match, int flag)
{
	int i;
	int c;
	int n;
	int j;
	int x;
	int diff;

	i = 0;
	j = 0;
	n = 0;
	x = 0;
	c = 0;
	diff = 0;
	while (match[j])
	{
		while (match[i + x] && match[i + x] != STAR)
		{
			if (i <= (int)ft_strlen(str) && match[i + x] != str[i])
			{
				if (match[i + x] == WHY && str[i] && ft_isprint(str[i]))
					diff -= 1;
				else if (match[i + x] == OP_SQUAR)
				{
					if (ft_strpchr(&match[i + x], CL_SQUAR) > 0 && ft_checkdeploy(&str[i], &match[i + x], flag, 0) >= SUCCESS)
					{
						x += ft_strpchr(&match[i + x], CL_SQUAR);
						diff -= 1;
					}
				}
				diff += 1;
			}
			++i;
		}
		j = i + x;
		n = i;
		while (match[j] && match[j] == STAR && match[j + 1] != '\0')
		{
			if (match[j + 1] != '\0' && match[j + 1] != STAR)
			{
				if (match[j + 1] != OP_SQUAR)
				{
					while (i <= (int)ft_strlen(str) && str[i] && str[i] != match[j + 1])
					{
						++i;
						if (str[i] == match[j + 1])
						{
							if (flag >= 2 && ft_isin(match[j + 1], &str[i + 1]))
								++i;
						}
					}
					if (i <= (int)ft_strlen(str) && str[i] != match[j + 1])
					{
						diff += 1;
					}
				}
				else
				{
					c = ft_checkdeploy(&str[i], &match[j + 1], flag, 1);
					while (ft_isprint(c) && str[i] != c)
						i++;
					if (c == ERROR)
						diff += 1;
					x += ft_strpchr(&match[i + x], CL_SQUAR) + 1;
					j += ft_strpchr(&match[j], CL_SQUAR);
					if (flag >= 2 && !match[j + 1])
						++i;
				}
				n = i + 1;
				if (match[j + 1] == STAR && match[j + 2] == OP_SQUAR)
					i++;
			}
			++j;
		}
		while (match[j] && match[j] != STAR)
		{
			if (i <= (int)ft_strlen(str) && match[j] != str[i])
			{
				if (match[j] == WHY && str[i] && ft_isprint(str[i]))
				{
					diff -= 1;
					}
				if (match[j] == OP_SQUAR)
				{
					if ((ft_strpchr(&match[i + x], CL_SQUAR)) > 0 && ft_checkdeploy(&str[i], &match[j], flag, 0) >= SUCCESS)
					{
						j += ft_strpchr(&match[i + x], CL_SQUAR);
						x += ft_strpchr(&match[i + x], CL_SQUAR) - 1;
						diff -= 1;
					}
				}
				diff += 1;
			}
			++i;
			if (match[j] != STAR)
				++j;
		}
		while (i <= (int)ft_strlen(str) && str[i] && match[j] && match[j] == STAR && match[j + 1] == '\0' && !diff)
			++i;
		if (!match[j])
			break ;
		++j;
		if ((i + x + 1) <= (int)ft_strlen(match) && match[i + x + 1] == STAR)
			++x;
	}
	if (flag == 2 && !diff)
		return(&str[i]);
	else if (flag == 1 && !diff)
		return ((n != 0) ? &str[n] : str);
	else if (flag == 3)
		return ((((int)ft_strlen(str) != i) || diff) ? ft_strdup(EMPTY_STR) : str);
	return (str);
}

char	*ft_strmatch(char *token, char *match, char flag)
{
	char *ret;

	ret = NULL;
	if (!match || !*match)
		ret = token;
	else
	{
		ret = ft_starmatch(token, match, flag);
	}
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

/* still need to fix the management of positional parameters and arrays. see bash man p 28 */

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
		if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0
				&& !(ft_isalpha(token[0][(int)ft_strlen(g_svar->key) + 1])
					|| ft_isdigit(token[0][(int)ft_strlen(g_svar->key) + 1])
					|| token[0][(int)ft_strlen(g_svar->key) + 1] == UNDERSCORE))
		{
			ft_strdel(token);
			*token = ft_strmatch(g_svar->value, word, flag);
			g_svar = tmp;
			ft_strdel(&word);
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	*token = ft_strdup(EMPTY_STR);
	ft_strdel(&word);
	g_svar = tmp;
	return (SUCCESS);
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

char *ft_strrev(char *token)
{
	int i;
	int len;
	char tmp;

	i = 0;
	len = ft_strlen(token) - 1;
	while (i < len)
	{
		tmp = token[len];
		token[len] = token[i];
		token[i] = tmp;
		i++;
		len--;
	}
	return (token);
}

int		opercent_exp(char **token)
{
	int flag;
	char *word;
	char *value;
	struct s_svar *tmp;

	tmp = g_svar;
	value = NULL;
	flag = (!(ft_spechrlen(*token))) ? 2 : 1;
	word = ft_strcdup(ft_strchr(*token, PERCENT) + flag, CL_BRACE);
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0
				&& !(ft_isalpha(token[0][(int)ft_strlen(g_svar->key) + 1])
					|| ft_isdigit(token[0][(int)ft_strlen(g_svar->key) + 1])
					|| token[0][(int)ft_strlen(g_svar->key) + 1] == UNDERSCORE))
		{
			free(*token);
			value = ft_strdup(g_svar->value);
			*token = ft_strmatch(ft_strrev(value), word, flag);
			*token = ft_strrev(*token);
			g_svar = tmp;
			ft_strdel(&word);
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	*token = ft_strdup(EMPTY_STR);
	g_svar = tmp;
	return (SUCCESS);
}
