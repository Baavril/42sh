/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:22:55 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/16 17:01:25 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_VARIABLES_H
# define SHELL_VARIABLES_H

struct	s_shvar
{
	char				*value;
	struct s_shvar		*next_var;
	struct s_shvar		*next_content;
	unsigned long long	index:63;
	_Bool				isarray:1;	
};

extern struct s_shvar		*g_shellvar;

int	initialize_shell_variables(char *argv);

int	shellvar_assignement(const char *const str);

void	free_all_shvar(void);

struct s_shvar	*create_shvar_node(char *value, struct s_shvar *next_content, struct s_shvar *next_var, int index);

/* Utils */
int		get_index(char *str);
_Bool	contains_array_subscript(char *str);

#endif
