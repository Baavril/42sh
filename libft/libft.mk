# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:45:47 by abarthel          #+#    #+#              #
#    Updated: 2020/01/03 14:01:42 by tgouedar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SOURCES_PATH :=	./src/

SOURCES	:=	ds_btree/btree_apply_infix.c \
		ds_btree/btree_apply_postfix.c \
		ds_btree/btree_apply_prefix.c \
		ds_btree/btree_apply_by_level.c \
		ds_btree/btree_create_node.c \
		ds_btree/btree_insert_data.c \
		ds_btree/btree_level_count.c \
		ds_btree/btree_search_data.c \
		ds_btree/btree_delete.c \
		ds_bstree/bstree_remove_data.c \
		ds_queue/queue_create_node.c \
		ds_queue/queue_enqueue.c \
		ds_queue/queue_dequeue.c \
		ds_queue/queue_front.c \
		ds_queue/queue_reverse.c \
		ds_queue/queue_reverse_recursion.c \
		ds_queue/queue_delete.c \
		ds_queue/queue_sort.c \
		ds_queue/queue_isempty.c \
		ds_queue/queue_size.c \
		ds_queue/queue_apply_to_each.c \
		ds_singly_linked_list/ft_lstadd.c \
		ds_singly_linked_list/ft_lstdel.c \
		ds_singly_linked_list/ft_lstdelone.c \
		ds_singly_linked_list/ft_lstiter.c \
		ds_singly_linked_list/ft_lstmap.c \
		ds_singly_linked_list/ft_lstnew.c \
		ds_stack/stack_apply_to_each.c \
		ds_stack/stack_create_element.c \
		ds_stack/stack_delete.c \
		ds_stack/stack_duplicate.c \
		ds_stack/stack_initialize.c \
		ds_stack/stack_isempty.c \
		ds_stack/stack_peek.c \
		ds_stack/stack_pop.c \
		ds_stack/stack_pop_get_data.c \
		ds_stack/stack_push.c \
		ds_stack/stack_reverse.c \
		ds_stack/stack_reverse_recursion.c \
		ds_stack/stack_sort.c \
		ds_stack/stack_swap.c \
		f_ctype/ft_isalnum.c \
		f_ctype/ft_isalpha.c \
		f_ctype/ft_isascii.c \
		f_ctype/ft_isdigit.c \
		f_ctype/ft_tolower.c \
		f_ctype/ft_toupper.c \
		f_ctype/ft_isupper.c \
		f_errno/error_msg.c \
		f_misc/ft_pow.c \
		f_misc/ft_strfchr.c \
		f_misc/ft_strnjoinfree.c \
		f_misc/ft_isspace.c \
		f_misc/ft_chrsearch.c \
		f_misc/ft_ewcsnwidth.c \
		f_misc/ft_ewcswidth.c \
		f_misc/ft_ewcwidth.c \
		f_misc/ft_fgetline.c \
		f_misc/ft_fprintbits.c \
		f_misc/ft_fputwcbits.c \
		f_misc/ft_fputwsbits.c \
		f_misc/ft_indice.c \
		f_misc/ft_isempty.c \
		f_misc/ft_isprime.c \
		f_misc/ft_isprint.c \
		f_misc/ft_itoa.c \
		f_misc/ft_memalloc.c \
		f_misc/ft_memdel.c \
		f_misc/ft_nmemdel.c \
		f_misc/ft_numlen.c \
		f_misc/ft_print_tables.c \
		f_misc/ft_printbits.c \
		f_misc/ft_putaddr.c \
		f_misc/ft_putchar_fd.c \
		f_misc/ft_putendl.c \
		f_misc/ft_putendl_fd.c \
		f_misc/ft_putllnb.c \
		f_misc/ft_putnbr.c \
		f_misc/ft_putnbr_base.c \
		f_misc/ft_putnbr_fd.c \
		f_misc/ft_putnbr_lowhexa.c \
		f_misc/ft_putnbr_octal.c \
		f_misc/ft_putnbr_upphexa.c \
		f_misc/ft_putstr.c \
		f_misc/ft_putnstr.c \
		f_misc/ft_putstr_fd.c \
		f_misc/ft_putuint.c \
		f_misc/ft_putuint_octal.c \
		f_misc/ft_putwcbits.c \
		f_misc/ft_putwstr.c \
		f_misc/ft_resolvepath.c \
		f_misc/ft_sortopt.c \
		f_misc/ft_str_is_alpha.c \
		f_misc/ft_strlower.c \
		f_misc/ft_str_is_lowercase.c \
		f_misc/ft_str_is_numeric.c \
		f_misc/ft_str_is_printable.c \
		f_misc/ft_str_is_uppercase.c \
		f_misc/ft_strclen.c \
		f_misc/ft_strclr.c \
		f_misc/ft_strdel.c \
		f_misc/ft_strendcpy.c \
		f_misc/ft_strequ.c \
		f_misc/ft_striter.c \
		f_misc/ft_striteri.c \
		f_misc/ft_strjoin.c \
		f_misc/ft_strjoinfree.c \
		f_misc/ft_strjoin_free.c \
		f_misc/ft_strmap.c \
		f_misc/ft_strmapi.c \
		f_misc/ft_strnequ.c \
		f_misc/ft_strnew.c \
		f_misc/ft_strnjoin.c \
		f_misc/ft_strrep.c \
		f_misc/ft_strsplit.c \
		f_misc/ft_strsplit_whitespaces.c \
		f_misc/ft_strsub.c \
		f_misc/ft_strtrim.c \
		f_misc/ft_swap.c \
		f_misc/ft_tabcpy.c \
		f_misc/ft_tab_rangecpy.c \
		f_misc/ft_tabdel.c \
		f_misc/ft_tablen.c \
		f_misc/ft_tabmalloc.c \
		f_misc/get_next_line.c \
		f_misc/utf8.c \
		f_misc/ft_lst_mergesort.c \
		f_misc/ft_lstadd_back.c \
		f_misc/ft_isin.c \
		f_ncurses/ft_getch.c \
		f_stdio/ft_perror.c \
		f_stdio/ft_putchar.c \
		f_stdio/ft_strerror.c \
		f_stdio/printf/cast.c \
		f_stdio/printf/dispatcher.c \
		f_stdio/printf/format.c \
		f_stdio/printf/ft_asprintf.c \
		f_stdio/printf/ft_b.c \
		f_stdio/printf/ft_chr.c \
		f_stdio/printf/ft_double.c \
		f_stdio/printf/ft_dprintf.c \
		f_stdio/printf/ft_expand_ret.c \
		f_stdio/printf/ft_hexa.c \
		f_stdio/printf/ft_n.c \
		f_stdio/printf/ft_nbr.c \
		f_stdio/printf/ft_octal.c \
		f_stdio/printf/ft_p.c \
		f_stdio/printf/ft_printf.c \
		f_stdio/printf/ft_printf_prs.c \
		f_stdio/printf/ft_str.c \
		f_stdio/printf/ft_unbr.c \
		f_stdio/printf/ft_vasprintf.c \
		f_stdio/printf/ft_vdprintf.c \
		f_stdio/printf/ft_y.c \
		f_stdio/printf/prefix.c \
		f_stdio/printf/prs_get.c \
		f_stdio/printf/str_format.c \
		f_stdio/printf/wrapper.c \
		f_stdlib/ft_atoi.c \
		f_stdlib/ft_atou.c \
		f_stdlib/ft_getenv.c \
		f_stdlib/ft_realpath.c \
		f_stdlib/ft_setenv.c \
		f_stdlib/ft_unsetenv.c \
		f_string/ft_memccpy.c \
		f_string/ft_memchr.c \
		f_string/ft_memcmp.c \
		f_string/ft_memcpy.c \
		f_string/ft_memmove.c \
		f_string/ft_memset.c \
		f_string/ft_isnumber.c \
		f_string/ft_isnumber_base.c \
		f_string/ft_strcat.c \
		f_string/ft_strchr.c \
		f_string/ft_strcmp.c \
		f_string/ft_strcpy.c \
		f_string/ft_strdup.c \
		f_string/ft_strlcat.c \
		f_string/ft_strlen.c \
		f_string/ft_strncat.c \
		f_string/ft_strncmp.c \
		f_string/ft_strncpy.c \
		f_string/ft_strndup.c \
		f_string/ft_strnstr.c \
		f_string/ft_strrchr.c \
		f_string/ft_strsep.c \
		f_string/ft_strstr.c \
		f_string/ft_strtok.c \
		f_strings/ft_bzero.c \
		f_strings/ft_strcasecmp.c \
		f_unistd/ft_getopt_gnu.c \
		f_unistd/ft_getopt_osx.c \
		f_wchar/ft_fputwc.c \
		f_wchar/ft_fputws.c \
		f_wchar/ft_wcscmp.c \
		f_wchar/ft_wcscpy.c \
		f_wchar/ft_wcslen.c \

OBJECTS := $(patsubst %.c,%.o,$(addprefix $(SOURCES_PATH), $(SOURCES)))

INCLUDES := ./include/

DEPENDS := $(patsubst %.c,%.d,$(addprefix $(SOURCES_PATH), $(SOURCES)))

ARFLAGS := rc

CFLAGS += -Wall -Werror -Wextra -ansi -std=c99 -D_POSIX_C_SOURCE -fno-builtin -O2
