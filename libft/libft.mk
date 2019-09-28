# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:45:47 by abarthel          #+#    #+#              #
#    Updated: 2019/09/25 15:20:10 by yberramd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SOURCES_PATH :=	./src/

SOURCES	:=	cast.c \
			dispatcher.c \
			error_msg.c \
			format.c \
			ft_atoi.c \
			ft_asprintf.c \
			ft_b.c \
			ft_bzero.c \
			ft_chr.c \
			ft_chrsearch.c \
			ft_dprintf.c \
			ft_double.c \
			ft_ewcsnwidth.c \
			ft_ewcswidth.c \
			ft_ewcwidth.c \
			ft_fgetline.c \
			ft_expand_ret.c \
			ft_fprintbits.c \
			ft_fputwc.c \
			ft_fputwcbits.c \
			ft_fputws.c \
			ft_fputwsbits.c \
			ft_hexa.c \
			ft_getch.c \
			ft_getenv.c \
			ft_getopt_gnu.c \
			ft_getopt_osx.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isempty.c \
			ft_isprime.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_lstadd.c \
			ft_lstdel.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_memalloc.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memdel.c \
			ft_memmove.c \
			ft_memset.c \
			ft_n.c \
			ft_nbr.c \
			ft_numlen.c \
			ft_octal.c \
			ft_p.c \
			ft_perror.c \
			ft_print_tables.c \
			ft_printbits.c \
			ft_printf.c \
			ft_printf_prs.c \
			ft_putaddr.c \
			ft_putchar.c \
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
			ft_putstr_fd.c \
			ft_putuint.c \
			ft_putuint_octal.c \
			ft_putwcbits.c \
			ft_putwchar.c \
			ft_putwstr.c \
			ft_setenv.c \
			ft_sortopt.c \
			ft_str.c \
			ft_str_is_alpha.c \
			ft_str_is_lowercase.c \
			ft_str_is_numeric.c \
			ft_str_is_printable.c \
			ft_str_is_uppercase.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strclen.c \
			ft_strclr.c \
			ft_strcasecmp.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdel.c \
			ft_strdup.c \
			ft_strendcpy.c \
			ft_strequ.c \
			ft_strerror.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlen.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strncat.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strndup.c \
			ft_strnequ.c \
			ft_strnew.c \
			ft_strnjoin.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strrep.c \
			ft_strsep.c \
			ft_strsplit.c \
			ft_strsplit_whitespaces.c \
			ft_strstr.c \
			ft_strsub.c \
			ft_strtok.c \
			ft_strtrim.c \
			ft_resolvepath.c \
			ft_realpath.c \
			ft_swap.c \
			ft_tabcpy.c \
			ft_tabdel.c \
			ft_tablen.c \
			ft_tabmalloc.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_unbr.c \
			ft_unsetenv.c \
			ft_vasprintf.c \
			ft_vdprintf.c \
			ft_wcscmp.c \
			ft_wcscpy.c \
			ft_wcslen.c \
			ft_y.c \
			get_next_line.c \
			prefix.c \
			prs_get.c \
			str_format.c \
			utf8.c \
			wrapper.c \
			ft_isspace.c \

OBJECTS := $(patsubst %.c,%.o,$(addprefix $(SOURCES_PATH), $(SOURCES)))

INCLUDES := ./include/

DEPENDS := $(patsubst %.c,%.d,$(addprefix $(SOURCES_PATH), $(SOURCES)))

ARFLAGS := rc

CFLAGS += -Wall -Werror -Wextra -ansi -std=c99 -D_POSIX_C_SOURCE -fno-builtin -O2
