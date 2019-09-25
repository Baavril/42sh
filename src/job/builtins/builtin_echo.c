/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/21 19:13:09 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cmd_echo(int argc, char **argv)
{
	int	i;

	(void)argc;
	i = 1;
	while (argv[i])
	{
		if (argv[i + 1])
		{
			ft_printf("%s ", argv[i]);
		}
		else
		{
			ft_printf("%s\n", argv[i]);
		}
		++i;
	}
	return (0);
}
