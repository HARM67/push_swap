#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include "ft_printf.h"
# include "get_next_line.h"
# define ABS(x) ((x > 0) ? x : -x)
# define MAX_BLOCK 0.3

typedef struct s_table t_table;
typedef struct s_elem	t_elem;
typedef struct s_stack	t_stack;
typedef struct s_app	t_app;

struct					s_elem
{
	long int			nbr;
	long int			pre_nbr;
	t_elem				*next;
	t_elem				*previous;
	t_elem				*pre_next;
	char				change;
	char				what_stack;
	unsigned int		read_nbr;
	unsigned int		current_nbr;
	unsigned int		block_nbr;
};

struct					s_table
{
	unsigned int		size;
	int		*data;
};

struct					s_block
{
	unsigned int		id;
	unsigned int		size;
	t_elem				*first;
	t_elem				*last;
};

struct					s_stack
{
	t_elem				*first;
	t_elem				*second;
	t_elem				*last;
	unsigned int		size;
	unsigned int		stack_nbr;
};

struct					s_app
{
	int					ac;
	char				**av;
	unsigned int		nbr_nb;
	t_stack				a;
	t_stack				b;
	t_elem				*pre;
	int					tmp;
	char				color;
	char				debug;
	char				manual;
	char				manual_debug;
	char				file;
	char				highlight;
	char				result;
	int					temoin;
	t_table				statistic;
};

void					init_app(t_app **app, int ac, char **av);
void					run_app(t_app *app);
void					free_app(t_app **app);

void					put_error(void);

void					init_stack(t_app *app);
void					free_stack(t_app *app);

void					read_arg(t_app *app);
void					print_stack(t_stack *stack, t_app *app);
void					print_stacks(t_app *app);
void					conform_stack(t_stack *stack);

void					swap(t_stack *stack);
void					push(t_stack *dest, t_stack *src);
void					rotate(t_stack *stack);
void 					reverse_rotate(t_stack *stack);

int						manual_reverse_rotate(t_app *app, char *tmp);
int						manual_rotate(t_app *app, char *tmp);
int						manual_push(t_app *app, char *tmp);
int						manual_swap(t_app *app, char *tmp);
void					manual(t_app *app);

void					pre_resolve(t_app *app);

void					resolve(t_app *app);
int						control(t_app *app);

int						need_swap_ab(t_app *app);
int						need_swap_a(t_app *app);
int						need_swap_b(t_app *app);
int						need_push2(t_app *app);
int						need_push(t_app *app);

t_elem					*new_elem(long int data, t_elem *previous);
void					control_double(t_stack *stack);

void					from_file(t_app *app);

long int				ft_atoi_8(const char *str);

int						ft_strtest(char *str, int (*f)(int));
int						control_arg(char *str);

void					read_elem(t_app *app, int i,unsigned int nbr_nb);

void					manual_debug(t_app *app);

void					multi_push(unsigned int nb, t_stack *dest, t_stack *src);
void					multi_swap(unsigned int nb, t_stack *stack);
void					multi_rotate(unsigned int nb, t_stack *stack);
void					multi_reverse(unsigned int nb, t_stack *stack);

void					make_statistic(t_app *app);
void					make_statistic_current(t_app *app);

void					create_table(t_table *table, unsigned int size);
void					print_table(t_table *table, t_app *app);
void					fill_table(t_app *app);

void					set_stack_numbers(t_app *app);
int						for_block(int nb, t_app *app);
void					identify_block(t_app *app);
#endif
