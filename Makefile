NAME = push_swap
INCLUDES=./includes
COMPILER = gcc
LIB=./
SRCS=main.c error.c app.c stack.c list.c command.c manual.c pre_resolve.c \
	resolve.c resolve2.c util.c get_next_line.c file.c ft_atoi_8.c \
	ft_strtest.c list2.c manual_debug.c statistic.c table.c block.c \
	zone.c calc_stat.c print_stack.c need_swap.c nav.c makecost.c go.c
SRC_PATH=./srcs/
OBJ=$(SRCS:.c=.o)
FLAG= -g
#-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDES)/get_next_line.h $(INCLUDES)/push_swap.h $(INCLUDES)/push_swap.h
	$(COMPILER) -o $(NAME) -I$(INCLUDES) $(OBJ) -L$(LIB) -lftprintf

%.o: $(SRC_PATH)%.c
	$(COMPILER) -c $(FLAG) $< -I$(INCLUDES)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
