# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:45:47 by abarthel          #+#    #+#              #
#    Updated: 2020/06/01 15:30:22 by tgouedar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SOURCES_PATH :=	./src/

SOURCES	:=	btree_apply_infix.c \
		btree_apply_postfix.c \
		btree_apply_prefix.c \
		btree_apply_by_level.c \
		btree_create_node.c \
		btree_insert_data.c \
		btree_level_count.c \
		btree_search_data.c \
		btree_delete.c \
		bstree_remove_data.c \
		queue_create_node.c \
		queue_enqueue.c \
		queue_dequeue.c \
		queue_front.c \
		queue_reverse.c \
		queue_reverse_recursion.c \
		queue_delete.c \
		queue_sort.c \
		queue_isempty.c \
		queue_size.c \
		queue_apply_to_each.c \
		ft_lstadd.c \
		ft_lstadd_back.c \
		ft_lstdel.c \
		ft_lstdelone.c \
		ft_lstpop.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstnew.c \
		stack_apply_to_each.c \
		stack_create_element.c \
		stack_delete.c \
		stack_duplicate.c \
		stack_initialize.c \
		stack_isempty.c \
		stack_peek.c \
		stack_pop.c \
		stack_pop_get_data.c \
		stack_push.c \
		stack_reverse.c \
		stack_reverse_recursion.c \
		stack_sort.c \
		stack_swap.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_isupper.c \
		error_msg.c \
		ft_pow.c \
		ft_strfchr.c \
		ft_strnjoinfree.c \
		ft_isspace.c \
		ft_chrsearch.c \
		ft_ewcsnwidth.c \
		ft_ewcswidth.c \
		ft_ewcwidth.c \
		ft_fgetline.c \
		ft_fprintbits.c \
		ft_fputwcbits.c \
		ft_fputwsbits.c \
		ft_indice.c \
		ft_isempty.c \
		ft_isprime.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memalloc.c \
		ft_memdel.c \
		ft_nmemdel.c \
		ft_numlen.c \
		ft_print_tables.c \
		ft_printbits.c \
		ft_putaddr.c \
		ft_putchar_fd.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_putllnb.c \
		ft_putnbr.c \
		ft_putnbr_base.c \
		ft_putnbr_fd.c \
		ft_putnbr_lowhexa.c \
		ft_putnbr_octal.c \
		ft_putnbr_upphexa.c \
		ft_putstr.c \
		ft_putnstr.c \
		ft_putstr_fd.c \
		ft_putnstr_fd.c \
		ft_putuint.c \
		ft_putuint_octal.c \
		ft_putwcbits.c \
		ft_putwstr.c \
		ft_resolvepath.c \
		ft_sortopt.c \
		ft_str_is_alpha.c \
		ft_strlower.c \
		ft_str_is_lowercase.c \
		ft_str_is_numeric.c \
		ft_str_is_printable.c \
		ft_str_is_uppercase.c \
		ft_strclen.c \
		ft_strclr.c \
		ft_strdel.c \
		ft_strendcpy.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strjoinfree.c \
		ft_strjoin_free.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnjoin.c \
		ft_strrep.c \
		ft_strsplit.c \
		ft_strsplit_whitespaces.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_swap.c \
		ft_tabcpy.c \
		ft_tab_rangecpy.c \
		ft_tabdel.c \
		ft_tablen.c \
		ft_tabmalloc.c \
		get_next_line.c \
		utf8.c \
		ft_lst_mergesort.c \
		ft_lstadd_back.c \
		ft_isin.c \
		ft_getch.c \
		ft_perror.c \
		ft_putchar.c \
		ft_strerror.c \
		ft_printf/cast.c \
		ft_printf/dispatcher.c \
		ft_printf/format.c \
		ft_printf/ft_asprintf.c \
		ft_printf/ft_b.c \
		ft_printf/ft_chr.c \
		ft_printf/ft_double.c \
		ft_printf/ft_dprintf.c \
		ft_printf/ft_expand_ret.c \
		ft_printf/ft_hexa.c \
		ft_printf/ft_n.c \
		ft_printf/ft_nbr.c \
		ft_printf/ft_octal.c \
		ft_printf/ft_p.c \
		ft_printf/ft_printf.c \
		ft_printf/ft_printf_prs.c \
		ft_printf/ft_str.c \
		ft_printf/ft_unbr.c \
		ft_printf/ft_vasprintf.c \
		ft_printf/ft_vdprintf.c \
		ft_printf/ft_y.c \
		ft_printf/prefix.c \
		ft_printf/prs_get.c \
		ft_printf/str_format.c \
		ft_printf/wrapper.c \
		ft_atoi.c \
		ft_atou.c \
		ft_getenv.c \
		ft_realpath.c \
		ft_setenv.c \
		ft_unsetenv.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_isnumber.c \
		ft_isnumber_base.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdup.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_display_len.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strndup.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strcspn.c \
		ft_strqchr.c \
		ft_strsep.c \
		ft_strstr.c \
		ft_strtok.c \
		ft_bzero.c \
		ft_strcasecmp.c \
		ft_getopt_gnu.c \
		ft_getopt_osx.c \
		ft_fputwc.c \
		ft_fputws.c \
		ft_wcscmp.c \
		ft_wcscpy.c \
		ft_wcslen.c \

OBJECTS := $(patsubst %.c,%.o,$(addprefix $(SOURCES_PATH), $(SOURCES)))

INCLUDES := ./include/

DEPENDS := $(patsubst %.c,%.d,$(addprefix $(SOURCES_PATH), $(SOURCES)))

ARFLAGS := rc

CFLAGS += -Wall -Werror -Wextra -ansi -std=c99 # -fsanitize=address -fno-optimize-sibling-calls
