/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:44:48 by abarthel          #+#    #+#             */
/*   Updated: 2019/11/09 15:45:40 by abarthel         ###   ########.fr       */
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

int	unglue_sep(char **input);

#endif