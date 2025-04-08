#include "ft_printf.h"

void	print_char(char c, t_arg *arg, int *count)
{
	if (arg->flag[0])
	{
		ft_cputchar(c, count);
		print_surplus(arg->width - 1, ' ', count);
	}
	else
	{
		print_surplus(arg->width - 1, ' ', count);
		ft_cputchar(c, count);
	}
}

void	print_string(char *str, t_arg *arg, int *count)
{
	int	dup;

	if (!str)
		str = "(null)";
	dup = 0;
	if ((unsigned int)arg->prec < ft_strlen(str) && arg->prec >= 0)
	{
		str = ft_strdup(str);
		str[arg->prec] = '\0';
		dup = 1;
	}
	if (!arg->flag[0])
		print_surplus(arg->width - ft_strlen(str), ' ', count);
	ft_cputstr(str, count);
	if (arg->flag[0])
		print_surplus(arg->width - ft_strlen(str), ' ', count);
	if (dup)
		free(str);
}

void	print_persent(t_arg *arg, int *count)
{
	if (arg->flag[0])
	{
		ft_cputchar('%', count);
		print_surplus(arg->width - 1, ' ', count);
	}
	else if (arg->flag[3])
	{
		print_surplus(arg->width - 1, '0', count);
		ft_cputchar('%', count);
	}
	else if (!arg->flag[0])
	{
		print_surplus(arg->width - 1, ' ', count);
		ft_cputchar('%', count);
	}
}
