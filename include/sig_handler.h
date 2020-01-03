/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 22:36:47 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/02 19:44:14 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_HANDLER_H
# define SIG_HANDLER_H

# define FATHER			0
# define CHILD			1

typedef void			(*t_ft_handler)(int);
typedef void			(*t_ft_sigact_handler)(int, siginfo_t *, void *);


typedef struct			s_sig
{
	int					sig_nbr;
	t_ft_handler		handlers[2];
}						t_sig;


void					ft_sigchld_handler(int nbr);

void					set_signals(int id);

#endif
