/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:51:41 by abarthel          #+#    #+#             */
/*   Updated: 2020/07/08 18:45:16 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

enum							e_minishell_error
{
	e_success,
	e_invalid_input,
	e_syntax_error,
	e_unexpected_eof,
	e_no_builtin,
	e_bad_substitution,
	e_cannot_assign_list_to_array_member,
	e_not_found,
	e_ambiguous_redirect,
	e_permission_denied,
	e_is_a_directory,
	e_no_such_file_or_directory,
	e_not_a_valid_file,
	e_incorrect_fd,
	e_filename_arg_required,
	e_cannot_allocate_memory,
	e_system_call_error,
	e_command_not_found,
	e_resource_tmp_unavailable,
	e_division_zero,
	e_assign_nonvar,
	e_missing_operand,
	e_missing_operator,
	e_arg_to_unary,
	e_base_error,
	e_invalid_name,
	e_invalid_number,
	e_invalid_base,
	e_neg_exp,
	e_empty_file,
	e_history_specification_out_of_range
};

enum							e_error_message_types
{
	e_invalid_type,
	e_parsing_type,
	e_cmd_type,
	e_builtin_type,
	e_maths_type
};

typedef enum e_minishell_error	t_error;

struct							s_error_desc
{
	int		code;
	char	*message;
};

extern char						*g_progname;

int								ft_clean_exit(char **av, int exit_status);
void							psherror(int e_error, char *str,
														int e_message_type);

#endif
