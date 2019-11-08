# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    42sh.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:45:47 by abarthel          #+#    #+#              #
#    Updated: 2019/11/08 16:35:03 by abarthel         ###   ########.fr        #
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
						lex/separators/unglue_sep.c \
						synt/synt.c \
						synt/synt_const.c \
						jcont/jcont.c \
						job/job.c \
						job/path_concat.c \
						job/builtins/builtin_alias.c \
						job/builtins/builtin_cd.c \
						job/builtins/builtin_echo.c \
						job/builtins/builtin_type.c \
						job/builtins/builtin_env.c \
						job/builtins/builtin_exit.c \
						job/builtins/builtin_pwd.c \
						job/builtins/builtin_hash.c \
						job/builtins/builtin_history.c \
						job/builtins/builtin_setenv.c \
						job/builtins/builtin_unsetenv.c \
						job/builtins/builtin_truefalse.c \
						job/builtins/builtin_test/builtin_test_free.c \
						job/builtins/builtin_test/builtin_test_tools.c \
						job/builtins/builtin_test/builtin_test_dispatchers.c \
						job/builtins/builtin_test/builtin_test_tokenisation.c \
						job/builtins/builtin_test/builtin_test_single_options1.c \
						job/builtins/builtin_test/builtin_test_single_options2.c \
						job/builtins/builtin_test/builtin_test_single_options3.c \
						job/builtins/builtin_test/builtin_test_single_options4.c \
						job/builtins/builtin_test/builtin_test_single_options5.c \
						job/builtins/builtin_test/builtin_test_double_options1.c \
						job/builtins/builtin_test/builtin_test_double_options2.c \
						job/builtins/builtin_test/builtin_test_precedence_management1.c \
						job/builtins/builtin_test/builtin_test_precedence_management2.c \
						job/builtins/builtins_dispatcher.c \
						job/builtins/ft_putenv_table.c \
						hash_module/bash_routines.c \
						hash_module/corps_fini_tools.c \
						hash_module/ft_empty_htable.c \
						hash_module/ft_free_htable.c \
						hash_module/ft_get_entry.c \
						hash_module/ft_del_entry.c \
						hash_module/ft_hash.c \
						hash_module/ft_hash_path.c \
						hash_module/ft_insert.c \
						hash_module/ft_iter_htable.c \
						hash_module/ft_lst_entries.c \
						hash_module/ft_print_entries.c \
						hash_module/htable_type_dispatcher.c \
						hash_module/init_htable.c \
						hash_module/string_routines.c \

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
