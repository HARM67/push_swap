NAME = push_swap
INCLUDES=./includes
COMPILER = gcc
LIB=./ft_printf/
SRCS=main.c error.c app.c stack.c list.c command.c manual.c pre_resolve.c \
	resolve.c util.c get_next_line.c file.c ft_atoi_8.c \
	ft_strtest.c list2.c manual_debug.c \
	zone.c calc_stat.c print_stack.c need_swap.c nav.c makecost.c go.c \
	come_to_start.c go_b.c for_resolution.c resolution.c command_lst.c \
	do_command.c
SRC_PATH=./srcs/
OBJ=$(SRCS:.c=.o)
FLAG= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): lib $(OBJ) $(INCLUDES)/get_next_line.h $(INCLUDES)/push_swap.h \
			$(INCLUDES)/push_swap.h
	$(COMPILER) -o $(NAME) -I$(INCLUDES) $(OBJ) -L$(LIB) -lftprintf

lib:
	make -C $(LIB)

lib_re:
	make re -C $(LIB)

%.o: $(SRC_PATH)%.c
	$(COMPILER) -c $(FLAG) $< -I$(INCLUDES)

clean:
	rm -f $(OBJ)
	make clean -C $(LIB)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIB)

re: fclean lib_re $(NAME)
