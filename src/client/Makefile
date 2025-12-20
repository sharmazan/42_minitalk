NAME = client
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = ../ft_printf
LIBFTPRINTF = $(LIBFT_PATH)/libftprintf.a

SOURCES =	client.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(LIBFTPRINTF) $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) $(LIBFTPRINTF)

$(LIBFTPRINTF):
	$(MAKE) -C $(LIBFT_PATH)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJECTS)

re: fclean all

.PHONY: all clean tests re fclean
