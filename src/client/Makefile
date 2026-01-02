NAME = client
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_PATH = ../libft
LIBFT = $(LIBFT_PATH)/libft.a
FTPRINTF_PATH = ../ft_printf
LIBFTPRINTF = $(FTPRINTF_PATH)/libftprintf.a
HEADER = ../inc/ft_header.h

SOURCES =	client.c client_utils.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(LIBFTPRINTF) $(LIBFT) $(OBJECTS) $(HEADER)
	$(CC) -o $(NAME) $(OBJECTS) $(LIBFTPRINTF) $(LIBFT)

$(LIBFTPRINTF):
	$(MAKE) -C $(FTPRINTF_PATH)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJECTS)

re: fclean all

.PHONY: all clean tests re fclean
