NAME = cub3d
CFLAGS = -g3 -fsanitize=address
MAKE = make

# ********************** Checking OS **********************
ifeq ($(UNAME), Darwin) # iMac / iOS
	CC = @cc
	LFLAGS += -framework OpenGL -framework AppKit
else #Linux and others...
	CC = @cc
	# LFLAGS += -lbsd -lXext -lX11 -lm
	LFLAGS += -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lz -lX11 -lm
endif

# ********************** Colors **********************
BRED="\033[132m"
BCYAN="\033[136m"
BYELLOW="\033[133m"
NC="\033[0m"
# BOLD="\033[1m"
# RESET="\033[0m"
# LIGHT_RED="\033[91m"
# LIGHT_GREEN="\033[92m"
# LIGHT_CYAN="\033[96m"

# ********************** Library's folders **********************
LIBS = libs
LIBFT = $(LIBS)/libft
GNL = $(LIBS)/getnextline
# MLX = $(LIBS)/mlx

# ********************** Library's **********************
INCLUDES = -Iincludes 
LIBS_A = $(addprefix $(LIBFT), /libft.a)
# LIBS_A += $(addprefix $(MLX), /libmlx.a) 
LIBS_A += $(addprefix $(GNL), /gnl.a)

# ********************** Project Files **********************
PARSING = parsing/
PARSING_FILES= about_map.c data_checks.c general_utils.c pars_colors.c parser.c

# ********************** Project Files **********************
SRC = src/
SRC_FILES= main.c

UTILS = $(SRC)utils/
UTILS_FILES= math_utils.c helpers.c render_utils.c render_helpers.c

REDNRING = $(UTILS)rendring/
REDNRING_FILES= mlx_utils.c events.c dda.c  raycasting.c  events_utils.c

FILES = $(addprefix $(SRC), $(SRC_FILES))
FILES += $(addprefix $(UTILS), $(UTILS_FILES))
FILES += $(addprefix $(REDNRING), $(REDNRING_FILES))
FILES += $(addprefix $(PARSING), $(PARSING_FILES))

# ********************** OBJ Files **********************
OBJ = $(FILES:.c=.o)

# ********************** Making RULES **********************
all: gnl libft $(NAME)
	@echo "${YELLOW}Cub3d is ready."

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

# mlx_clean:
# 	@cd $(MLX) && $(MAKE) clean

gnl_fclean:
	@cd $(GNL) && $(MAKE) fclean

gnl_clean:
	@cd $(LIBFT) && $(MAKE) clean

# clean: mlx_clean libft_clean gnl_clean
# 	rm -f $(OBJ)

clean:  libft_clean gnl_clean
	rm -f $(OBJ)

# fclean: clean mlx_clean libft_fclean gnl_fclean
# 	@rm -f $(NAME)

fclean: clean  libft_fclean gnl_fclean
	@rm -f $(NAME)

# .PHONY: all clean fclean re libft mlx libft_clean mlx_clean libft_fclean gnl_clean gnl_fclean
.PHONY: all clean fclean re libft  libft_clean  libft_fclean gnl_clean gnl_fclean
