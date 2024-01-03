NAME = cub3d
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
MAKE = make
LFLAGS = -lmlx -framework OpenGL -framework AppKit

# ********************** Colors **********************
BRED=\033[132m
BCYAN=\033[136m
BYELLOW=\033[133m
NC=\033[0m

# ********************** Library's folders **********************
LIBS = libs
LIBFT = $(LIBS)/libft
GNL = $(LIBS)/getnextline

# ********************** Library's **********************
INCLUDES = -Iincludes 
LIBS_A = $(addprefix $(LIBFT), /libft.a)
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
	@echo "${YELLOW}Cub3d is ready.${NC}"

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

gnl_fclean:
	@cd $(GNL) && $(MAKE) fclean

gnl_clean:
	@cd $(LIBFT) && $(MAKE) clean

clean:  libft_clean gnl_clean
	rm -f $(OBJ)



fclean: clean  libft_fclean gnl_fclean
	@rm -f $(NAME)


.PHONY: all clean fclean re libft  libft_clean  libft_fclean gnl_clean gnl_fclean
