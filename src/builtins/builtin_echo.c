/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/02/01 14:18:58 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		cmd_echo(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		ft_putstr(argv[i++]);
		if (i < argc)
			ft_putstr(" ");
	}
	ft_putstr("\n");
	return (0);
}
