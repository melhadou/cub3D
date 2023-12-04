NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -c
RM = rm -rf
MANK = test.c
MANDATORY = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_memcpy.c ft_memmove.c \
			ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c \
			ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c \
			ft_memchr.c ft_memcmp.c ft_calloc.c ft_substr.c ft_strtrim.c ft_strjoin.c \
			ft_split.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_strmapi.c ft_striteri.c ft_itoa.c \

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
				ft_lstmap_bonus.c \

MAN=$(MANDATORY:%.c=%.o)
BON=$(BONUS:%.c=%.o)

# Defaulte Target
all: $(NAME)
	@echo "Making libft.a"

$(NAME): $(MAN)

bonus: $(MAN) $(BON)

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
