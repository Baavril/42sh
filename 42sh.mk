# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    42sh.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:45:47 by abarthel          #+#    #+#              #
#    Updated: 2019/12/14 18:29:13 by tgouedar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 42sh

SOURCES_PATH	:= ./src/

SOURCES			:=		main.c \
						transversal/error.c \
						transversal/signals.c \
						input/input.c \
						input/history.c \
						input/keys.c \
						input/prompt.c \
						input/quote.c \
						input/display.c \
						input/analyzer.c \
						input/keyboard_commands.c \
						input/keyboard_dispatcher.c \
						input/auto_completion/auto_completion.c \
						input/auto_completion/tst.c \
						lexer/lexer.c \
						lexer/grammar_symbols.c \
						lexer/separators/unglue_metachr.c \
						lexer/separators/pipeline_separators.c \
						expansions/expansions.c \
						expansions/substitutions.c \
						job_control/synt.c \
						job_control/synt_const.c \
						job_control/jcont.c \
						job_control/ft_add_process.c \
						job_control/ft_free_job.c \
						job_control/ft_get_job.c \
						job_control/ft_get_process_pid.c \
						job_control/ft_isnumber.c \
						job_control/ft_new_job.c \
						job_control/ft_print_job.c \
						job_control/ft_set_prio.c \
						job_control/ft_sigchld_handler.c \
						job_control/ft_update_job_status.c \
						job_control/path_concat.c \
						job_control/get_sequence.c \
						builtins/builtin_alias.c \
						builtins/builtin_set.c \
						builtins/builtin_unset.c \
						builtins/builtin_export.c \
						builtins/builtin_cd.c \
						builtins/builtin_echo.c \
						builtins/builtin_type.c \
						builtins/builtin_env.c \
						builtins/builtin_exit.c \
						builtins/builtin_pwd.c \
						builtins/builtin_hash.c \
						builtins/builtin_history.c \
						builtins/builtin_setenv.c \
						builtins/builtin_unsetenv.c \
						builtins/builtin_truefalse.c \
						builtins/builtin_fc.c \
						builtins/builtin_test/test_free.c \
						builtins/builtin_test/test_tools.c \
						builtins/builtin_test/test_dispatchers.c \
						builtins/builtin_test/test_tokenisation.c \
						builtins/builtin_test/test_single_options1.c \
						builtins/builtin_test/test_single_options2.c \
						builtins/builtin_test/test_single_options3.c \
						builtins/builtin_test/test_single_options4.c \
						builtins/builtin_test/test_single_options5.c \
						builtins/builtin_test/test_double_options1.c \
						builtins/builtin_test/test_double_options2.c \
						builtins/builtin_test/test_precedence_mgt1.c \
						builtins/builtin_test/test_precedence_mgt2.c \
						builtins/builtins_dispatcher.c \
						builtins/ft_putenv_table.c \
						transversal/hash/bash_routines.c \
						transversal/hash/corps_fini_tools.c \
						transversal/hash/ft_empty_htable.c \
						transversal/hash/ft_free_htable.c \
						transversal/hash/ft_get_entry.c \
						transversal/hash/ft_del_entry.c \
						transversal/hash/ft_hash.c \
						transversal/hash/ft_hash_path.c \
						transversal/hash/ft_insert.c \
						transversal/hash/ft_iter_htable.c \
						transversal/hash/ft_lst_entries.c \
						transversal/hash/ft_print_entries.c \
						transversal/hash/htable_type_dispatcher.c \
						transversal/hash/init_htable.c \
						transversal/hash/string_routines.c \
						transversal/shell_variables/shell_variables.c \
						LL_parser/debug_gnt.c \
						LL_parser/debug_interpreter.c \
						LL_parser/io_redirect.c \
						LL_parser/is_potential.c \
						LL_parser/parser.c \
						LL_parser/pipe_sequence.c \
						LL_parser/simple_command.c \
						LL_parser/terminals.c \
						LL_parser/wordtypes.c \
						interpreter/interpreter.c

#						job_control/job.c

OBJECTS := $(patsubst %.c,%.o,$(addprefix $(SOURCES_PATH), $(SOURCES)))

PATH_LIB := ./libft/

INCLUDES := -I./include/ -I$(PATH_LIB)include/

DEPENDS := $(patsubst %.c,%.d,$(addprefix $(SOURCES_PATH), $(SOURCES)))

SH := bash --posix

TESTS_PATH := ./tools/

TESTS_SCRIPT := launch_test.sh "launch from makefile"

TEST := $(SH) $(TESTS_PATH)$(TESTS_SCRIPT)

LDLIBS += -ltermcap  $(PATH_LIB)libft.a

LDFLAGS += $(CDEBUG)

CFLAGS += -Wall -Wextra -Werror -ansi -D_POSIX_C_SOURCE=200809L -std=c99 $(CDEBUG)
#CFLAGS += -fno-builtin -O2

CDEBUG += -g -fsanitize=address
