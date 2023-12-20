NAME = cub3d
CFLAGS =  -g3 -fsanitize=address
MAKE = make

# ********************** Checking OS **********************
ifeq ($(UNAME), Darwin) # iMac / iOS
	CC = gcc
	LFLAGS += -framework OpenGL -framework AppKit
else #Linux and others...
	CC = gcc
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
MLX = $(LIBS)/mlx

# ********************** Library's **********************
INCLUDES = -Iincludes 
LIBS_A = $(addprefix $(MLX), /libmlx.a) $(addprefix $(LIBFT), /libft.a)

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

# ********************** OBJ Files **********************
OBJ = $(FILES:.c=.o)

# ********************** Making RULES **********************
all: libft mlx $(NAME)
	@echo "${YELLOW}Cub3D is ready to play${NC}"

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS_A) $(LFLAGS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libft:
	@cd $(LIBFT) && $(MAKE)

mlx:
	@cd $(MLX) && $(MAKE)

re: fclean all

# ********************** Cleaning RULES **********************
libft_clean:
	@cd $(LIBFT) && $(MAKE) clean

mlx_clean:
	@cd $(MLX) && $(MAKE) clean

libft_fclean:
	@cd $(LIBFT) && $(MAKE) fclean

clean: mlx_clean libft_clean
	rm -f $(OBJ)

fclean: clean mlx_clean libft_fclean
	@rm -f $(NAME)

.PHONY: all clean fclean re libft mlx libft_clean mlx_clean libft_fclean
