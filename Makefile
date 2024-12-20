NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I ./includes/

SRC_DIR = .
BIN_DIR = ./bin

SOURCES = main.c \
			src/utils/ft_error.c

OBJECTS = $(addprefix $(BIN_DIR)/,$(SOURCES:.c=.o))

MAKE_LIBFT = $(MAKE) -C ./src/utils/libft -s
LIBFT = ./src/utils/libft/libft.a

MAKE_GARBAGE = $(MAKE) -C ./src/utils/garbage_collector -s
GARBAGE = ./src/utils/garbage_collector/garbage_collector.a

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(MAKE_GARBAGE)
	@$(MAKE_LIBFT)
	@$(CC) $(OBJECTS) -o $@ $(INCLUDES) $(GARBAGE) $(LIBFT) src/utils/libmlx42.a -ldl -lglfw -pthread -lm
	@echo "\033[1;38;5;10m   ⭐ - All files compiled.\033[0m"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	@rm -rf $(BIN_DIR)
	@$(MAKE_GARBAGE) -s clean
	@$(MAKE_LIBFT) -s clean
	@find . -name '*.o' -delete
	@echo "\033[1;38;5;226m   📂 - bin folders removed.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE_GARBAGE) -s fclean
	@$(MAKE_LIBFT) -s fclean
	@echo "\033[1;38;5;9m   📤 - Libs and executable removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re
