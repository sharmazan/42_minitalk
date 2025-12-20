SERVER = server
CLIENT = client
SRC_PATH = src
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = $(SRC_PATH)/ft_printf
SERVER_PATH = $(SRC_PATH)/$(SERVER)
CLIENT_PATH = $(SRC_PATH)/$(CLIENT)
LIBFT_PATH = $(SRC_PATH)/ft_printf
LIBFTPRINTF = $(LIBFT_PATH)/libftprintf.a


all: $(SERVER)

$(SERVER): $(LIBFTPRINTF)
	$(MAKE) -C $(SERVER_PATH)
	cp $(SERVER_PATH)/$(SERVER) .

$(LIBFTPRINTF):
	$(MAKE) -C $(LIBFT_PATH)

fclean: clean
	rm -f $(SERVER)
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(MAKE) -C $(SERVER_PATH) fclean

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(SERVER_PATH) clean

re: fclean all

.PHONY: all clean tests re fclean
