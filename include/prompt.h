/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:33:04 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/27 14:09:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "libft.h"
# include "input.h"

size_t	search_prompt(t_cursor *cursor, char *buff);
size_t	mk_prompt(char **prompt, char *prompt_var);
int		mkprompt_quote(char *input, char **buff, size_t *len);
char	*mkprompt_expand(const char *ps1, size_t *len);

#endif
