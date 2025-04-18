# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/18 13:41:46 by jodiaz-a          #+#    #+#              #
#    Updated: 2025/02/19 08:16:42 by tclaereb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#########################################
## ARGUMENTS
#########################################

INCLUDES_PATH	= ../../includes
NAME			= libft.a
CFLAGS			= -Wextra -Wall -Werror -g3 -I$(INCLUDES_PATH)
CC				= gcc

BIN_DIR = ./bin

########################################
## SOURCES
########################################

SOURCES	=	ft_isalpha.c	\
		ft_isdigit.c	\
		ft_isalnum.c	\
		ft_isascii.c	\
		ft_isprint.c	\
		ft_isgraph.c	\
		ft_strlen.c	\
		ft_memset.c	\
		ft_bzero.c	\
		ft_memcpy.c	\
		ft_memmove.c	\
		ft_strlcpy.c	\
		ft_strlcat.c	\
		ft_toupper.c	\
		ft_tolower.c	\
		ft_strchr.c	\
		ft_strrchr.c	\
		ft_strncmp.c	\
		ft_memchr.c	\
		ft_memcmp.c	\
		ft_strnstr.c	\
		ft_atoi.c	\
		ft_atol.c	\
		ft_calloc.c	\
		ft_strdup.c	\
		ft_substr.c	\
		ft_strjoin.c	\
		ft_strtrim.c	\
		ft_split.c		\
		ft_itoa.c		\
		ft_atol.c	\
		ft_strmapi.c	\
		ft_striteri.c	\
		ft_putchar_fd.c	\
		ft_putstr_fd.c	\
		ft_putendl_fd.c	\
		ft_putnbr_fd.c	\
		ft_printf.c		\
		ft_print_c.c	\
		ft_print_d_and_i.c	\
		ft_print_p.c	\
		ft_print_s.c	\
		ft_print_u.c	\
		ft_print_xx.c	\
		ft_lstnew.c		\
		ft_lstadd_front.c	\
		ft_lstsize.c	\
		ft_lstlast.c	\
		ft_lstadd_back.c	\
		ft_lstdelone.c	\
		ft_lstclear.c	\
		ft_lstiter.c	\
		ft_lstmap.c		\
			get_next_line_bonus.c	\
			get_next_line_utils_bonus.c	\
			ft_abs.c


OBJS_FILES		= $(addprefix $(BIN_DIR)/,$(SOURCES:.c=.o))

########################################
## RULES
########################################


all: $(NAME)

$(NAME): $(OBJS_FILES)
	$(AR) rcs $@ $^

$(BIN_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BIN_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
