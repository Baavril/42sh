/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 15:26:07 by bprunevi          #+#    #+#             */
/*   Updated: 2019/10/20 11:26:11 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
#define DISPLAY_H
#include "libft.h"

void display_init(int sig);
int display(char *str, size_t j, size_t i, size_t u, char *prompt, size_t prompt_len);

#endif
