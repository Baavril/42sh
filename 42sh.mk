# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    42sh.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:45:47 by abarthel          #+#    #+#              #
#    Updated: 2020/01/26 19:00:52 by yberramd         ###   ########.fr        #
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
						input/termcaps/termcaps.c \
						lexer/lexer.c \
						lexer/grammar_symbols.c \
						lexer/separators/unglue_metachr.c \
						lexer/separators/pipeline_separators.c \
						globing/globing_substitutions.c \
						globing/pattern_matching.c \
						globing/pattern_matching_tools.c \
						globing/pattern_why_matching.c \
						globing/pattern_matching_deployement.c \
						globing/pattern_deploy_launcher.c \
						globing/pattern_deploy_maker.c \
						globing/pattern_matching_core.c \
						expansions/global_exp/expansions_main.c \
						expansions/global_exp/expansions_split.c \
						expansions/global_exp/expansions_bslash.c \
						expansions/global_exp/expansions_checker.c \
						expansions/global_exp/expansions_between.c \
						expansions/global_exp/expansions_identifier.c \
						expansions/global_exp/potential_libft_functions.c \
						expansions/global_exp/tilde_substitutions.c \
						expansions/global_exp/direct_substitutions.c \
						expansions/global_exp/simple_substitutions.c \
						expansions/global_exp/why_substitutions.c \
						expansions/global_exp/plus_substitutions.c \
						expansions/global_exp/dash_substitutions.c \
						expansions/global_exp/equal_substitutions.c \
						expansions/global_exp/sharp_substitutions.c \
						expansions/global_exp/bsharp_substitutions.c \
						expansions/global_exp/percent_substitutions.c \
						expansions/maths_exp/operations/addition.c \
						expansions/maths_exp/operations/assign.c \
						expansions/maths_exp/operations/assign_bitwise.c \
						expansions/maths_exp/operations/assign_op.c \
						expansions/maths_exp/operations/bitwise.c \
						expansions/maths_exp/operations/bitwise_shifts.c \
						expansions/maths_exp/operations/comma.c \
						expansions/maths_exp/operations/compare.c \
						expansions/maths_exp/operations/equality_test.c \
						expansions/maths_exp/operations/increment.c \
						expansions/maths_exp/operations/logic.c \
						expansions/maths_exp/operations/multiplication.c \
						expansions/maths_exp/ft_build_ast.c \
						expansions/maths_exp/ft_eval.c \
						expansions/maths_exp/ft_free_ast.c \
						expansions/maths_exp/ft_int64_convert.c \
						expansions/maths_exp/ft_itoa64.c \
						expansions/maths_exp/maths_dispatcher.c \
						expansions/maths_exp/maths_expansion.c \
						expansions/maths_exp/maths_lexer.c \
						expansions/maths_exp/maths_parser.c \
						expansions/maths_exp/maths_token.c \
						expansions/maths_exp/operand_token.c \
						expansions/maths_exp/parentheses.c \
						expansions/maths_exp/parse_incr.c \
						expansions/maths_exp/shvar_tools.c \
						job_control/ft_launch_job.c \
						job_control/ft_add_process.c \
						job_control/ft_free_job.c \
						job_control/ft_free_jcont.c \
						job_control/ft_get_job.c \
						job_control/ft_pop_job.c \
						job_control/ft_get_process_pid.c \
						job_control/ft_add_job.c \
						job_control/ft_print_job.c \
						job_control/ft_set_prio.c \
						job_control/ft_sigchld_handler.c \
						job_control/ft_update_job_status.c \
						job_control/ft_wait_foreground.c \
						job_control/path_concat.c \
						job_control/get_sequence.c \
						builtins/builtin_alias/cmd_alias.c \
						builtins/builtin_alias/cmd_unalias.c \
						builtins/builtin_alias/alias_tools.c \
						builtins/builtin_cd/cmd_cd.c \
						builtins/builtin_cd/file_stats.c \
						builtins/builtin_cd/ft_simplify_path.c \
						builtins/builtin_cd/path_tools.c \
						builtins/builtin_set.c \
						builtins/builtin_unset.c \
						builtins/builtin_export.c \
						builtins/builtin_echo.c \
						builtins/builtin_type.c \
						builtins/builtin_exit.c \
						builtins/builtin_hash.c \
						builtins/builtin_history.c \
						builtins/builtin_truefalse.c \
						builtins/builtin_fc.c \
						builtins/builtin_jcont/cmd_bg.c \
						builtins/builtin_jcont/cmd_fg.c \
						builtins/builtin_jcont/cmd_jobs.c \
						builtins/builtin_jcont/resume_job.c \
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
						transversal/hash/bash_routines.c \
						transversal/hash/corps_fini_tools.c \
						transversal/hash/random_tools.c \
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
						LL_parser/gnt.c \
						LL_parser/io_redirect.c \
						LL_parser/is_potential.c \
						LL_parser/parser.c \
						LL_parser/pipe_sequence.c \
						LL_parser/simple_command.c \
						LL_parser/terminals.c \
						LL_parser/wordtypes.c \
						interpreter/interpreter.c \
						interpreter/i_simple_command.c \
						interpreter/eval_command.c \
						interpreter/i_redirect.c \
						interpreter/i_redirect_and.c \
						interpreter/i_heredoc.c \
						interpreter/i_open_on_fd.c \
						interpreter/free.c

#						job_control/job.c

OBJECTS := $(patsubst %.c,%.o,$(addprefix $(SOURCES_PATH), $(SOURCES)))

PATH_LIB := ./libft/
LIBFT := $(PATH_LIB)libft.a

INCLUDES := -I./include/ -I$(PATH_LIB)include/

DEPENDS := $(patsubst %.c,%.d,$(addprefix $(SOURCES_PATH), $(SOURCES)))

SH := bash --posix

TESTS_PATH := ./tools/

TESTS_SCRIPT := launch_test.sh "launch from makefile"

TEST := $(SH) $(TESTS_PATH) $(TESTS_SCRIPT)

LDLIBS += -ltermcap $(PATH_LIB)libft.a

LDFLAGS += $(CDEBUG)

CFLAGS += -Wall -Wextra -Werror -ansi -D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=200809L -std=c99 $(CDEBUG)

#CFLAGS += -fno-builtin -O2

CDEBUG += -g  -fsanitize=address -fno-optimize-sibling-calls
