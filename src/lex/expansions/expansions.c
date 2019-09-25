/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:07:44 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/01 18:48:23 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "error.h"
#include "expansions.h"

const struct s_tags	g_tags[] =
{
	{"${", &parameter_expansions, "}"},
	{"$", &parameter_expansions, ""},
	{"~", &tilde_expansion, ""},
	{"\0", NULL, NULL}
};

static int	expansion_dispatcher(char *str)
{
	int	i;
	int	ref;
	char	*ptr;
	char	*closest;

	i = 0;
	closest = NULL;
	ref = -1;
	while (*(g_tags[i].opentag))
	{
		ptr = ft_strstr(str, g_tags[i].opentag);
		if (ptr && (!closest || (ptr < closest && closest)))
		{
			closest = ptr;
			ref = i;
		}
		++i;
	}
	return (ref);
}

static char	*get_closest_exp(char *str)
{
	int	i;
	char	*ptr;
	char	*closest;

	i = 0;
	closest = NULL;
	while (*(g_tags[i].opentag))
	{
		ptr = ft_strstr(str, g_tags[i].opentag);
		if (ptr && (!closest || (ptr < closest && closest)))
			closest = ptr;
		++i;
	}
	return (closest);
}

static int		replace_expansion(char **token, char **next, int ref)
{
	static size_t	index;
	char		*new;
	size_t		lnew;
	size_t		lprefix;
	int		ret;

	ret = e_success;
	if (*token == *next)
		index = 0;
	lprefix = (size_t)((*next) - (*token));
	if (!(ret = g_tags[ref].f(&index, next, g_tags[ref].opentag, g_tags[ref].closetag)))
	{
		lnew = lprefix + ft_strlen(*next);
		new = (char*)ft_memalloc(sizeof(char) * (lnew + 1));
		ft_strncat(new, *token, lprefix);
		ft_memdel((void**)token);
		ft_strcat(new, *next);
		ft_memdel((void**)next);
		*next = &(new)[index + lprefix];
		*token = new;
		return (e_success);
	}
	return (ret);
}

int			treat_expansions(char **tokens)
{
	int	ref;
	int	i;
	int	ret;
	char	*next;

	i = 0;
	if (!tokens)
		return (e_invalid_input);
	/* Tokens might be wrong, strsplit is not ok fpor instance "echo ${LOGNAME }KO" does not work*/
	/*ft_print_tables(tokens);
	exit(1);
*/	/* END debugg */
	while (tokens[i])
	{
		next = tokens[i];
		while ((next = get_closest_exp(next)))
		{
			ref = expansion_dispatcher(next);
			if ((ret = replace_expansion(&tokens[i], &next, ref)))
			{
				psherror(ret, tokens[i], e_cmd_type);
				return (ret);
			}
		}
		++i;
	}
	return (e_success);
}
