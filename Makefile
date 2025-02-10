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
MLX 	= $(MLX_DIR)build/libmlx42.a $(PRFLAGS)

PARSING_DIR  = parsing/
PARSING		 = check_map parsing_utils parsing

RENDER_DIR = render/
RENDER    = player

SRC_FILES  += main utils
SRC_FILES  += $(addprefix $(PARSING_DIR), $(PARSING))
SRC_FILES  += $(addprefix $(RENDER_DIR), $(RENDER))

SRC         = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ         = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJ_CACHE   = .cache_exists

###

all: 			 $(MLX) $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) CFLAGS+=$(LIBFT_CFLAGS)

$(MLX):
	@make -C $(MLX_DIR)build 

$(NAME): 		$(OBJ)
					$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)
					@echo "\033[0;32m$(shell echo $(NAME) | tr '[:lower:]' '[:upper:]') : COMPILED\033[0m"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_CACHE)
					@echo "Compiling $<"
					@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJ_CACHE):
					@mkdir -p $(OBJ_DIR)
					@mkdir -p $(OBJ_DIR)$(PARSING_DIR)
					@mkdir -p $(OBJ_DIR)$(RENDER_DIR)

clean:
					@make clean -C $(LIBFT_DIR)
					$(RM) $(OBJ_DIR)
					$(RM) $(OBJ_CACHE)
					@echo "$(NAME) and libs object files cleaned!"

fclean: 		clean
					@make fclean -C $(LIBFT_DIR)
					$(RM) $(NAME)
					@echo "$(NAME) and libs executable files cleaned!"
					rm -f $(MLX_DIR)build/CMakeCache.txt

re: 			fclean all
					@echo "Cleaned and rebuilt everything for $(NAME)!"

.PHONY:			all clean fclean re

.SILENT: