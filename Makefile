NAME = push_swap
INCLUDES=./includes
COMPILER = gcc
LIB=./
SRCS=main.c error.c app.c stack.c list.c command.c manual.c pre_resolve.c \
	resolve.c resolve2.c util.c get_next_line.c file.c
SRC_PATH=./srcs/
OBJ=$(SRCS:.c=.o)
FLAG= -g
#-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(COMPILER) -o $(NAME) -I$(INCLUDES) $(OBJ) -L$(LIB) -lftprintf

%.o: $(SRC_PATH)%.c
	$(COMPILER) -c $(FLAG) $< -I$(INCLUDES)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

test: re
	./push_swap 78 42 -c -v
	./push_swap 42 78 -c -v
	./push_swap 78 50 42 -c -v
	./push_swap 78 42 50 -c -v
	./push_swap 42 50 78 -c -v
	./push_swap 42 78 50 -c -v
	./push_swap 42 50 80 78 -c -v
	./push_swap 3 2 1 4 -c -v
	./push_swap 1 4 3 2 -c -v
	./push_swap 1 2 3 4 -c -v
	./push_swap 8 5 6 3 1 2 -v -c
