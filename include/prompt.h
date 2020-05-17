/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:33:04 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/17 16:44:32 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "libft.h"
# include "input.h"

size_t	search_prompt(t_cursor *cursor, char *buff);
size_t	mkprompt(char **buff);
int		mkprompt_quote(char *input, char **buff, size_t *len);
char	*mkprompt_expand(const char *ps1, size_t *len);

#endif
