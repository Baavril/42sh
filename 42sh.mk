# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    42sh.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:45:47 by abarthel          #+#    #+#              #
#    Updated: 2019/09/27 13:08:07 by bprunevi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

SOURCES_PATH := ./src/

SOURCES :=	main.c \
			transv/error.c \
			transv/signals.c \
			input/input.c \
			input/history.c \
			input/keys.c \
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
			job/builtins/builtin_cd.c \
			job/builtins/builtin_echo.c \
			job/builtins/builtin_type.c \
			job/builtins/builtin_env.c \
			job/builtins/builtin_exit.c \
			job/builtins/builtin_pwd.c \
			job/builtins/builtin_setenv.c \
			job/builtins/builtin_unsetenv.c \
			job/builtins/builtin_truefalse.c \
			job/builtins/builtins_dispatcher.c \
			job/builtins/ft_putenv_table.c \

OBJECTS := $(patsubst %.c,%.o,$(addprefix $(SOURCES_PATH), $(SOURCES)))

PATH_LIB := ./libft/

INCLUDES := -I./include/ -I$(PATH_LIB)include/

DEPENDS := $(patsubst %.c,%.d,$(addprefix $(SOURCES_PATH), $(SOURCES)))

SH := bash --posix

TESTS_PATH := ./tools/

TESTS_SCRIPT := launch_test.sh "launch from makefile"

TEST := $(SH) $(TESTS_PATH)$(TESTS_SCRIPT)

LDLIBS += $(PATH_LIB)libft.a -l termcap

#LDFLAGS += -flto=full

CFLAGS += -Wall -Wextra -Werror -ansi -D_POSIX_C_SOURCE -std=c99

CFLAGS += -fno-builtin -O2
#CFLAGS += -g -fsanitize=address
