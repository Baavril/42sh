/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 10:44:25 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/16 14:31:33 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strsep(char **stringp, const char *delim)
{
	char	*token;
	char	*next;

	next = NULL;
	if (!*stringp)
		return (NULL);
	if (!**stringp)
		return (*stringp);
	token = *stringp;
	next = ft_strstr(*stringp, delim);
	while (delim && *delim && next && *next)
	{
		*next = '\0';
		++next;
		++delim;
	}
	*stringp = next;
	return (token);
}
