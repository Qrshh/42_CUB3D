NAME        = cub3d
INCLUDES    = includes/
SRC_DIR     = src/
OBJ_DIR     = obj/

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g3
PRFLAGS     = -L/opt/homebrew/lib -ldl -lglfw -pthread -lm
RM          = rm -rf

LIBFT_DIR    = $(INCLUDES)Libft/
LIBFT        = $(LIBFT_DIR)libft.a
LIBFT_CFLAGS = -fPIC

MLX_DIR = $(INCLUDES)MLX42/
MLX 	= $(MLX_DIR)build/libmlx42.a

PARSING_DIR  = parsing/
PARSING		 = check_map parsing_utils parsing parsing_path parsing_color

RENDER_DIR = render/
RENDER    = player print_utils

SRC_FILES  += main utils
SRC_FILES  += $(addprefix $(PARSING_DIR), $(PARSING))
SRC_FILES  += $(addprefix $(RENDER_DIR), $(RENDER))
SRC         = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ         = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJ_CACHE   = .cache_exists

###

all: 			 $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) CFLAGS+=$(LIBFT_CFLAGS) --quiet

MLX_BUILD_FLAG = $(MLX_DIR)build/mlx42_built

mlx: $(MLX)

$(MLX): 
	@echo "\033[0;33mBuilding MLX42...\033[0m"
	@if [ ! -d "$(MLX_DIR)build" ]; then mkdir -p $(MLX_DIR)build; fi
	@cmake -B $(MLX_DIR)build -S $(MLX_DIR) -DCMAKE_RULE_MESSAGES=OFF
	@cmake --build $(MLX_DIR)build -j4 > /dev/null
	@touch $(MLX_BUILD_FLAG)
	@echo "\033[0;32mMLX42 successfully built!\033[0m"

$(NAME): 		$(OBJ)
					$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(PRFLAGS) -o $(NAME)
					@echo "\033[0;32m$(shell echo $(NAME) | tr '[:lower:]' '[:upper:]') : COMPILED\033[0m"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_CACHE)
					@echo "Compiling $<"
					@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJ_CACHE):
					@mkdir -p $(OBJ_DIR)
					@mkdir -p $(OBJ_DIR)$(PARSING_DIR)
					@mkdir -p $(OBJ_DIR)$(RENDER_DIR)

clean:
					@make clean -C $(LIBFT_DIR) --quiet
					$(RM) $(OBJ_DIR)
					$(RM) $(OBJ_CACHE)
					@echo "$(NAME) and libs object files cleaned!"

fclean: 		clean
					@make fclean -C $(LIBFT_DIR) --quiet
					$(RM) $(NAME)
					@echo "$(NAME) and libs executable files cleaned!"
					rm -f $(MLX_DIR)build/CMakeCache.txt

mlx_clean:
				@if [ -d "$(MLX_DIR)build" ]; then \
					find $(MLX_DIR)build -type f -print -delete; \
					rm -rf $(MLX_DIR)build; \
					echo "\033[0;31mMLX42 cleaned!\033[0m"; \
				else \
					echo "\033[0;33mMLX42 build directory not found, nothing to clean.\033[0m"; \
				fi

re: 			fclean all
					@echo "Cleaned and rebuilt everything for $(NAME)!"

.PHONY:			all clean fclean re

.SILENT: