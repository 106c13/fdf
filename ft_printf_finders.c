#include "ft_printf.h"

void	find_specifier(const char **format, t_arg *arg)
{
	int	specifier;

	specifier = -1;
	if (**format == 'd' || **format == 'i')
		specifier = 0;
	else if (**format == 'c')
		specifier = 1;
	else if (**format == 's')
		specifier = 2;
	else if (**format == 'x')
		specifier = 3;
	else if (**format == 'X')
		specifier = 4;
	else if (**format == 'u')
		specifier = 5;
	else if (**format == 'p')
		specifier = 6;
	else if (**format == '%')
		specifier = 7;
	if (specifier != -1)
		(*format)++;
	arg->spec = specifier;
}

void	find_flag(const char **format, t_arg *arg)
{
	(*format)++;
	while (**format
		&& (**format == '-'
			|| **format == '+'
			|| **format == ' '
			|| **format == '0'
			|| **format == '#'))
	{
		if (**format == '-')
			arg->flag[0] = 1;
		else if (**format == '+')
			arg->flag[1] = 1;
		else if (**format == ' ')
			arg->flag[2] = 1;
		else if (**format == '0')
			arg->flag[3] = 1;
		else if (**format == '#')
			arg->flag[4] = 1;
		(*format)++;
	}
}

void	find_width(const char **format, t_arg *arg)
{
	arg->width = 0;
	while (**format >= '0' && **format <= '9')
	{
		arg->width = arg->width * 10 + **format - 48;
		(*format)++;
	}
}

void	find_precision(const char **format, t_arg *arg)
{
	arg->prec_bool = 0;
	if (**format == '.')
	{
		arg->prec = 0;
		(*format)++;
		while (**format >= '0' && **format <= '9')
		{
			arg->prec = arg->prec * 10 + **format - 48;
			(*format)++;
		}
		arg->prec_bool = 1;
	}
	else
		arg->prec = -1;
}
