/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:13:35 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/01 18:40:54 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H
# include <stdlib.h>

struct	s_tags
{
	char	*opentag;
	int	(*f)(size_t*, char**, const char*, const char*);
	char	*closetag;
};

struct	s_param
{
	char	*pname;
	char	*(*g)(const char*);
};

int		treat_expansions(char **tokens);

int		getenv_content(char **content, char *str, const char *closetag);

size_t		ft_varlen(const char *s, const char *closetag);

int		is_a_valid_chr(const char c);

int		is_valid_param(const char *str);

int		parameter_expansions(size_t *index, char **str,
		const char *opentag, const char *closetag);

int		tilde_expansion(size_t *index, char **str,
		const char *opentag, const char *closetag);

#endif
