# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    42sh.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:45:47 by abarthel          #+#    #+#              #
#    Updated: 2020/05/12 16:24:51 by yberramd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 42sh

SOURCES_PATH	:= ./src/

SOURCES			:=		transversal/program/main.c \
						transversal/program/error.c \
						transversal/program/signals.c \
						transversal/shell_variables/main.c \
						transversal/shell_variables/newnodshell.c \
						transversal/shell_variables/tools.c \
						transversal/shell_variables/update.c \
						transversal/hash/bash_routines.c \
						transversal/hash/corps_fini_tools.c \
						transversal/hash/random_tools.c \
						transversal/hash/ft_empty_htable.c \
						transversal/hash/ft_free_htable.c \
						transversal/hash/ft_get_entry.c \
						transversal/hash/ft_del_entry.c \
						transversal/hash/ft_hash.c \
						transversal/hash/ft_insert.c \
						transversal/hash/ft_iter_htable.c \
						transversal/hash/ft_lst_entries.c \
						transversal/hash/ft_print_entries.c \
						transversal/hash/htable_type_dispatcher.c \
						transversal/hash/init_htable.c \
						transversal/hash/string_routines.c \
						transversal/pattern_matching/main.c \
						transversal/pattern_matching/ft_alpharange.c \
						transversal/pattern_matching/tools.c \
						transversal/pattern_matching/recursion.c \
						transversal/pattern_matching/identifier.c \
						transversal/pattern_matching/tools.c \
						transversal/pattern_matching/recursion.c \
						transversal/pattern_matching/identifier.c \
						transversal/pattern_matching/simple_wildcards.c \
						transversal/pattern_matching/complex_wildcards.c \
						transversal/pattern_matching/deployement/main.c \
						transversal/pattern_matching/deployement/find.c \
						transversal/pattern_matching/deployement/tools.c \
						transversal/pattern_matching/deployement/launcher.c \
						transversal/pattern_matching/deployement/maker.c \
						input/input.c \
						input/prompt.c \
						input/search_prompt.c \
						input/quote.c \
						input/display.c \
						input/getstdin.c \
						input/analyzer.c \
						input/update_buffer.c \
						input/auto_completion/auto_completion.c \
						input/auto_completion/tst.c \
						input/auto_completion/binary.c \
						input/auto_completion/env_var.c \
						input/auto_completion/assign_binary.c \
						input/auto_completion/create_binary.c \
						input/auto_completion/path.c \
						input/termcaps/termcaps.c \
						input/history/history.c \
						input/history/history_search.c \
						input/history/init_history.c \
						input/history/mv_history.c \
						input/history/clean.c \
						input/history/exclamation.c \
						input/history/exclamation2.c \
						input/history/new_history.c \
						input/history/search_exclamation.c \
						input/history/ft_atoi_history.c \
						input/keys/autocompletion.c \
						input/keys/keyboard_commands.c \
						input/keys/keyboard_commands_ctrl.c \
						input/keys/keyboard_dispatcher.c \
						input/keys/keys.c \
						input/keys/keys_arrow.c \
						input/keys/keys_copypaste.c \
						input/keys/keys_navig.c \
						lexer/ft_trim_comment.c \
						lexer/lexer.c \
						lexer/lexer_verbose.c \
						lexer/get_token.c \
						lexer/quote.c \
						lexer/tokens.c \
						lexer/grammar_symbols.c \
						lexer/separators/unglue_metachr.c \
						lexer/separators/pipeline_separators.c \
						globing/main.c \
						globing/tools.c \
						globing/scanner.c \
						expansions/global_exp/main.c \
						expansions/global_exp/tools.c \
						expansions/global_exp/split.c \
						expansions/global_exp/quotes.c \
						expansions/global_exp/checker.c \
						expansions/global_exp/launcher.c \
						expansions/global_exp/generator.c \
						expansions/global_exp/inbetween.c \
						expansions/global_exp/backslash.c \
						expansions/global_exp/identifier.c \
						expansions/global_exp/management.c \
						expansions/substitutions/tilde.c \
						expansions/substitutions/direct.c \
						expansions/substitutions/simple.c \
						expansions/substitutions/plus.c \
						expansions/substitutions/dash.c \
						expansions/substitutions/equal.c \
						expansions/substitutions/sharp.c \
						expansions/substitutions/params.c \
						expansions/substitutions/percent.c \
						expansions/substitutions/positional.c \
						expansions/substitutions/begin_sharp.c \
						expansions/substitutions/question_mark.c \
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
						expansions/maths_exp/parse_sign.c \
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
						job_control/ft_transfersig.c \
						job_control/ft_update_job_status.c \
						job_control/ft_wait.c \
						job_control/path_concat.c \
						job_control/get_sequence.c \
						builtins/builtin_alias/cmd_alias.c \
						builtins/builtin_alias/cmd_unalias.c \
						builtins/builtin_alias/alias_tools.c \
						builtins/builtin_cd/cmd_cd.c \
						builtins/builtin_cd/file_stats.c \
						builtins/builtin_cd/ft_pcderror.c \
						builtins/builtin_cd/ft_simplify_path.c \
						builtins/builtin_cd/path_tools.c \
						builtins/builtin_set/main.c \
						builtins/builtin_set/positional_parameters.c \
						builtins/builtin_unset.c \
						builtins/builtin_echo.c \
						builtins/builtin_type.c \
						builtins/builtin_exit.c \
						builtins/builtin_hash.c \
						builtins/builtin_history.c \
						builtins/builtin_truefalse.c \
						builtins/builtin_fc/builtin_fc.c \
						builtins/builtin_fc/print_history.c \
						builtins/builtin_export/main.c \
						builtins/builtin_export/tools.c \
						builtins/builtin_export/var_checker.c \
						builtins/builtin_export/var_checker_env.c \
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
						LL_parser/gnt.c \
						LL_parser/io_redirect.c \
						LL_parser/is_potential.c \
						LL_parser/parser.c \
						LL_parser/pipe_sequence.c \
						LL_parser/simple_command.c \
						LL_parser/terminals.c \
						LL_parser/wordtypes.c \
						interpreter/interpreter.c \
						interpreter/i_comp.c \
						interpreter/i_pipe.c \
						interpreter/i_simple_command.c \
						interpreter/eval_command.c \
						interpreter/i_redirect.c \
						interpreter/i_redirect_and.c \
						interpreter/i_heredoc.c \
						interpreter/i_open_on_fd.c \
						interpreter/free.c \
						interpreter/curjob.c

#						job_control/job.c

OBJECTS := $(patsubst %.c,%.o,$(addprefix $(SOURCES_PATH), $(SOURCES)))

PATH_LIB := ./libft/
LIBFT := $(PATH_LIB)libft.a

HEADER_PATH :=	./include \
				$(PATH_LIB)include

INCLUDES :=	$(addprefix -I, $(HEADER_PATH))

DEPENDS := $(patsubst %.c,%.d,$(addprefix $(SOURCES_PATH), $(SOURCES)))

SH := bash --posix

TESTS_PATH := ./tools/

TESTS_SCRIPT := launch_test.sh "launch from makefile"

TEST := $(SH) $(TESTS_PATH) $(TESTS_SCRIPT)

LDLIBS += -ltermcap $(PATH_LIB)libft.a

LDFLAGS += $(CDEBUG)

CFLAGS += -Wall -Wextra -Werror -ansi -D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=200809L -std=c99 $(CDEBUG)

#CFLAGS += -fno-builtin -O2

CDEBUG += -g #-fsanitize=address -fno-optimize-sibling-calls
