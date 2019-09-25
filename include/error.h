/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:51:41 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/21 18:54:34 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

enum	e_minishell_error
{
	e_success,
	e_invalid_input,
	e_syntax_error,
	e_no_builtin,
	e_bad_substitution,
	e_filename_arg_required,
	e_cannot_allocate_memory,
	e_system_call_error,
	e_permission_denied,
	e_is_a_directory,
	e_command_not_found,
	e_no_such_file_or_directory,
	e_resource_tmp_unavailable
};

enum	e_error_message_types
{
	e_invalid_type,
	e_parsing_type,
	e_cmd_type
};

typedef enum e_minishell_error	t_error;

struct	s_error_desc
{
	int		code;
	char	*message;
};

extern const struct s_error_desc	g_errordesc[];
extern char	*g_progname;

void	psherror(int e_error, char *str, int e_message_type);

#endif
