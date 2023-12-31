NAME = cub3d
CFLAGS = #-Wall -Wextra -Werror -g3 -fsanitize=address
MAKE = make

# ********************** Checking OS **********************
ifeq ($(UNAME), Darwin) # iMac / iOS
	CC = @gcc
	LFLAGS += -framework OpenGL -framework AppKit
else #Linux and others...
	CC = @gcc
	LFLAGS += -lbsd -lXext -lX11 -lm
endif

# ********************** Colors **********************
BRED=\033[1;31m
BCYAN=\033[1;36m
BYELLOW=\033[1;33m
NC=\033[0m

# ********************** Library's folders **********************
LIBS = libs
LIBFT = $(LIBS)/libft
GNL = $(LIBS)/getnextline
MLX = $(LIBS)/mlx

# ********************** Library's **********************
INCLUDES = -Iincludes 
LIBS_A = $(addprefix $(MLX), /libmlx.a) $(addprefix $(LIBFT), /libft.a)
LIBS_A += $(addprefix $(GNL), /gnl.a)

# ********************** Project Files **********************
PARSING = parsing/
PARSING_FILES= about_map.c data_checks.c general_utils.c pars_colors.c parser.c

# ********************** Project Files **********************
SRC = src/
SRC_FILES= main.c

UTILS = $(SRC)utils/
UTILS_FILES= math_utils.c helpers.c

REDNRING = $(UTILS)rendring/
REDNRING_FILES= mlx_utils.c events.c dda.c  raycasting.c

FILES = $(addprefix $(SRC), $(SRC_FILES))
FILES += $(addprefix $(UTILS), $(UTILS_FILES))
FILES += $(addprefix $(REDNRING), $(REDNRING_FILES))
FILES += $(addprefix $(PARSING), $(PARSING_FILES))

# ********************** OBJ Files **********************
OBJ = $(FILES:.c=.o)

# ********************** Making RULES **********************
all: gnl libft mlx $(NAME)
	@echo "${YELLOW}Cub3D is ready to play${NC}"

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS_A) $(LFLAGS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libft:
	@cd $(LIBFT) && $(MAKE)

gnl:
	@cd $(GNL) && $(MAKE)

mlx:
	@cd $(MLX) && $(MAKE)

re: fclean all

# ********************** Cleaning RULES **********************
libft_clean:
	@cd $(LIBFT) && $(MAKE) clean

libft_fclean:
	@cd $(LIBFT) && $(MAKE) fclean

mlx_clean:
	@cd $(MLX) && $(MAKE) clean

gnl_fclean:
	@cd $(GNL) && $(MAKE) fclean

gnl_clean:
	@cd $(LIBFT) && $(MAKE) clean

clean: mlx_clean libft_clean gnl_clean
	rm -f $(OBJ)

fclean: clean mlx_clean libft_fclean gnl_fclean
	@rm -f $(NAME)

.PHONY: all clean fclean re libft mlx libft_clean mlx_clean libft_fclean gnl_clean gnl_fclean
