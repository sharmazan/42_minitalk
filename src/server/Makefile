NAME = server
# HEADER = libftprintf.h
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = ../ft_printf
LIBFTPRINTF = $(LIBFT_PATH)/libftprintf.a

SOURCES =	server.c

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
	$(MAKE) -C $(LIBFT_PATH) fclean

clean:
	rm -f $(OBJECTS)
	$(MAKE) -C $(LIBFT_PATH) clean

re: fclean all

.PHONY: all clean tests re fclean
