# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    42sh.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:45:47 by abarthel          #+#    #+#              #
#    Updated: 2019/11/09 11:41:50 by abarthel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 42sh

SOURCES_PATH	:= ./src/

SOURCES			:=		main.c \
						transv/error.c \
						transv/signals.c \
						input/input.c \
						input/history.c \
						input/keys.c \
						input/prompt.c \
						input/quote.c \
						input/display.c \
						lex/lexer.c \
						lex/expansions/expansions.c \
						lex/expansions/expansion_utils.c \
						lex/expansions/get_param.c \
						lex/expansions/parameter_expansions.c \
						lex/expansions/tilde_expansion.c \
						lex/separators/pipeline_separators.c \
						lex/separators/unglue_sep.c \
						jcont/synt.c \
						jcont/synt_const.c \
						jcont/jcont.c \
						jcont/job.c \
						jcont/path_concat.c \
						builtins/builtin_alias.c \
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
						transv/hash_module/bash_routines.c \
						transv/hash_module/corps_fini_tools.c \
						transv/hash_module/ft_empty_htable.c \
						transv/hash_module/ft_free_htable.c \
						transv/hash_module/ft_get_entry.c \
						transv/hash_module/ft_del_entry.c \
						transv/hash_module/ft_hash.c \
						transv/hash_module/ft_hash_path.c \
						transv/hash_module/ft_insert.c \
						transv/hash_module/ft_iter_htable.c \
						transv/hash_module/ft_lst_entries.c \
						transv/hash_module/ft_print_entries.c \
						transv/hash_module/htable_type_dispatcher.c \
						transv/hash_module/init_htable.c \
						transv/hash_module/string_routines.c \
						transv/shell_variables/assignement_shellvar.c \
						transv/shell_variables/utils_shell_variables.c \
						transv/shell_variables/tools_parser_shellvar.c \
						transv/shell_variables/shell_variables.c \

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

CFLAGS += -Wall -Wextra -Werror -ansi -D_POSIX_C_SOURCE -std=c99 $(CDEBUG)
#CFLAGS += -fno-builtin -O2

CDEBUG += -g -fsanitize=address
