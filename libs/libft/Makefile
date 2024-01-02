NAME = libft.a
CC = @cc
CFLAGS = -Wall -Wextra -Werror -c
RM = rm -rf
MANDATORY = ft_atoi.c ft_isdigit.c ft_strchr.c \
						ft_strdup.c ft_strlen.c ft_strncmp.c \
						ft_strrchr.c ft_substr.c \
						ft_strtrim.c ft_strjoin.c ft_split.c

MAN=$(MANDATORY:%.c=%.o)

# Defaulte Target
all: $(NAME)
	@echo "Making libft.a"

$(NAME): $(MAN)

%.o:%.c
	@echo  -n ". "
	@$(CC) $(CFLAGS) $<
	@ar -rc $(NAME) $@

clean:
	@echo "Cleaning obj: libft"
	@$(RM) *.o

fclean:
	@echo "Cleaning All: libft"
	@$(RM) *.o $(NAME)

re: fclean all 
