/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:44:48 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/29 15:52:36 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINES_H
# define PIPELINES_H

struct	s_pipeline_separators
{
	const char *const	sep;
};

struct	s_metachr
{
	const char *const	c;
};

_Bool	is_pipeline_separator(const char *str);

int		unglue_metachr(char **input);

#endif
