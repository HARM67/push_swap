#include "push_swap.h"

void	from_file(t_app *app)
{
	char	*file;
	int		print;

	print = 0;
	get_next_line(0, &file);
	if (!file)
		put_error();
	while (*file != 0)
	{
		if (app->debug && print)
		{
			ft_printf("%.3s", file - 1);
			print_stacks(app);
		}
		print = 1;
		if (manual_swap(app, file));
		else if (manual_push(app, file));
		else if (manual_reverse_rotate(app, file));
		else if (manual_rotate(app, file));
		else
			print = 0;
		file++;
	}
	if (app->debug == 0)
		print_stacks(app);
}
