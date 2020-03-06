/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 22:36:47 by tgouedar          #+#    #+#             */
/*   Updated: 2020/03/06 12:10:06 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_HANDLER_H
# define SIG_HANDLER_H

# define FATHER			0
# define CHILD			1
# define FORKED_CONTROL	2

typedef void			(*t_ft_handler)(int sig_nbr);

typedef struct			s_sig
{
	int					sig_nbr;
	t_ft_handler		handlers[3];
}						t_sig;

void					ft_sigchld_handler(int nbr);
void					ft_transfersig(int nbr);
void					ft_transferkill(int nbr);
void					ft_transferstop(int nbr);

void					set_signals(int id);

#endif
