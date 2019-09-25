/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:59:39 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/01 17:14:33 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "error.h"
#include "expansions.h"
#include "separators.h"

/* The lexer should tokenize || ; & && ect even if glued to words
 * example : echo ok;ls||env 
 * It manages expansions subsitution in ech tokens*/
char	**lexer(char **input)
{
	char	**tokens;
	char	**retsplit;
	int	ret;

	if ((ret = unglue_sep(input)))
	{
		psherror(ret, g_progname, e_cmd_type);
		return (NULL);
	}
	retsplit = ft_strsplit_whitespaces(*input);
	if (!retsplit || !retsplit[0])
	{
		ft_tabdel(&retsplit);
		return (NULL);
	}
	tokens = ft_tabcpy(retsplit);
	ft_tabdel(&retsplit);
	if (treat_expansions(tokens))
	{
		ft_tabdel(&tokens);
		return (NULL);
	}
	return (tokens);
}
