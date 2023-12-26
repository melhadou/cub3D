NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -c
RM = rm -rf
MANDATORY = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_memcpy.c ft_memmove.c \
			ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c \
			ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c \
			ft_memchr.c ft_memcmp.c ft_calloc.c ft_substr.c ft_strtrim.c ft_strjoin.c \
			ft_split.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_strmapi.c ft_striteri.c ft_itoa.c \

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
