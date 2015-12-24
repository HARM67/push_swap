#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include "ft_printf.h"
# include "get_next_line.h"

typedef struct s_elem	t_elem;
typedef struct s_stack	t_stack;
typedef struct s_app	t_app;

struct					s_elem
{
	long int					nbr;
	long int					pre_nbr;
	t_elem				*next;
	t_elem				*previous;
	t_elem				*pre_next;
	char				change;
};

struct					s_stack
{
	t_elem				*first;
	t_elem				*second;
	t_elem				*last;
};
struct					s_app
{
	int					ac;
	char				**av;
	int					nbr_nb;
	t_stack				a;
	t_stack				b;
	int					tmp;
	char				color;
	char				debug;
	char				manual;
	char				file;
	char				highlight;
	int					temoin;
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

void					pre_resolve(t_stack *stack);

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
#endif
