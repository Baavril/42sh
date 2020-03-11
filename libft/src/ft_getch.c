/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:36:04 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/01 09:53:15 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_getch(void)
{
	int	ch;

	if ((int)read(STDIN_FILENO, (void*)&ch, sizeof(char)) <= 0)
	{
		return (-1);
	}
	else
	{
		return (ch);
	}
}
