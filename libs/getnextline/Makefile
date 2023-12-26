NAME = gnl.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -c
RM = rm -rf
MANDATORY = get_next_line.c get_next_line_utils.c

MAN=$(MANDATORY:%.c=%.o)

all: $(NAME)

$(NAME): $(MAN)

%.o:%.c
	$(CC) $(CFLAGS) $<
	@ar -rc $(NAME) $@

clean:
	$(RM) *.o

fclean:
	$(RM) *.o $(NAME)

re: fclean all 
