/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:05:14 by abarthel          #+#    #+#             */
/*   Updated: 2019/11/13 12:05:19 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINES_H
# define PIPELINES_H

struct	s_pipeline_separators
{
	const char *const	sep;
};

extern const struct s_pipeline_separators	g_separators[];

_Bool	is_pipeline_separator(const char *str);
int		unglue_sep(char **input);
char	**get_sequence(char **cmd);
char	**position_token(char **cmd);
char	**jump_sep(char **cmd);

#endif
