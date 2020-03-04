# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/04 15:23:21 by bprunevi          #+#    #+#              #
#    Updated: 2020/03/04 15:23:23 by bprunevi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

-include 21sh.mk

.PHONY: all clean fclean re try_lib

all: try_lib $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@$(CC) $^ -o $@ $(LDLIBS) $(LDFLAGS)
	@printf "\n\e[38;5;44m%4s [\e[1m$(NAME) built]\n\n\e[0m"

try_lib:
	@$(MAKE) -j -C $(PATH_LIB)

clean:
	@$(RM) $(OBJECTS) $(DEPENDS)
	@$(MAKE) clean -C $(PATH_LIB)

fclean:
	@$(RM) $(OBJECTS) $(DEPENDS) $(NAME)
	@$(MAKE) fclean -C $(PATH_LIB)

re: fclean all

test: all
	@$(TEST)

-include $(DEPENDS)

%.o: %.c Makefile $(NAME).mk
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
	@printf "\e[38;5;155m%-24s \e[38;5;37mobject built\n\e[0m" $(notdir $(basename $@))
