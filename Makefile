SERVER = server
CLIENT = client
SRC_PATH = src
CC = cc
CFLAGS = -Wall -Wextra -Werror

SERVER_PATH = $(SRC_PATH)/$(SERVER)
CLIENT_PATH = $(SRC_PATH)/$(CLIENT)
LIBFT_PATH = $(SRC_PATH)/libft
LIBFT = $(LIBFT_PATH)/libft.a
FTPRINTF_PATH = $(SRC_PATH)/ft_printf
LIBFTPRINTF = $(FTPRINTF_PATH)/libftprintf.a
HEADER = src/inc/ft_header.h

SERVER_SOURCES = $(SERVER_PATH)/server.c
SERVER_OBJECTS = $(SERVER_SOURCES:.c=.o)

CLIENT_SOURCES = $(CLIENT_PATH)/client.c
CLIENT_OBJECTS = $(CLIENT_SOURCES:.c=.o)

all: $(SERVER) $(CLIENT)

$(SERVER): $(LIBFTPRINTF) $(SERVER_OBJECTS) $(HEADER)
	$(MAKE) -C $(SERVER_PATH)
	cp $(SERVER_PATH)/$(SERVER) .

$(CLIENT): $(LIBFTPRINTF) $(LIBFT) $(CLIENT_OBJECTS) $(HEADER)
	$(MAKE) -C $(CLIENT_PATH)
	cp $(CLIENT_PATH)/$(CLIENT) .

$(LIBFTPRINTF):
	$(MAKE) -C $(FTPRINTF_PATH)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

fclean: clean
	rm -f $(SERVER)
	rm -f $(CLIENT)
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(MAKE) -C $(FTPRINTF_PATH) fclean
	$(MAKE) -C $(SERVER_PATH) fclean
	$(MAKE) -C $(CLIENT_PATH) fclean

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(FTPRINTF_PATH) clean
	$(MAKE) -C $(SERVER_PATH) clean
	$(MAKE) -C $(CLIENT_PATH) clean

re: fclean all

.PHONY: all clean tests re fclean
