NAME = push_swap
INCLUDES=./includes
INCLUDES_FT_PRINTF=./ft_printf/includes
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
FLAG=-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(LIB)libftprintf.a $(OBJ) $(INCLUDES)/get_next_line.h $(INCLUDES_FT_PRINTF)/ft_printf.h \
	$(INCLUDES)/push_swap.h
	$(COMPILER) -o $(NAME) -I$(INCLUDES_FT_PRINTF) -I$(INCLUDES) $(OBJ) -L$(LIB) -lftprintf

%.o: $(SRC_PATH)%.c
	$(COMPILER) -c $(FLAG) $< -I$(INCLUDES_FT_PRINTF) -I$(INCLUDES)

$(LIB)libftprintf.a:
	make -C $(LIB)
	make clean -C $(LIB)

clean:
	make clean -C $(LIB)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIB)
	rm -f $(NAME)

re: fclean $(NAME)
