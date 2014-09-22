NAME    := zero
BIN_DIR := /usr/local/bin

all: build

build: $(NAME).c
	gcc -Wall -Wextra -o $(NAME) $< -lm -O2

test: build
	./$(NAME)

memcheck:
	gcc -Wall -Wextra -o $(NAME) $(NAME).c -lm -g -O0
	valgrind ./$(NAME)

install: build
	install -m 0755 $(NAME) $(BIN_DIR)

uninstall:
	rm -f $(BIN_DIR)/$(NAME)

clean:
	rm -f $(NAME)
