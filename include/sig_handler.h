/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 22:36:47 by tgouedar          #+#    #+#             */
/*   Updated: 2019/12/16 22:50:00 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_HANDLER_H
# define SIG_HANDLER_H

void			ft_sigchld_handler(int nbr);
void			ft_sigusr1_handler(int nbr, siginfo_t *siginfo, void *context);
void			ft_catch_sigusr1(int nbr);

void			set_signals(void);

#endif
