#include "ft_printf.h"

void	format_parser(const char **format, t_arg *arg)
{
	find_flag(format, arg);
	find_width(format, arg);
	find_precision(format, arg);
	find_specifier(format, arg);
}

int	string_builder(const char **format, va_list *args, int *count)
{
	t_arg	arg;

	ft_memset(arg.flag, 0, sizeof(arg.flag));
	format_parser(format, &arg);
	if (arg.spec == -1)
		return (0);
	if (arg.spec == 0)
		print_int(va_arg(*args, int), &arg, count);
	else if (arg.spec == 1)
		print_char((char)va_arg(*args, int), &arg, count);
	else if (arg.spec == 2)
		print_string(va_arg(*args, char *), &arg, count);
	else if (arg.spec == 3)
		print_hex((unsigned int)va_arg(*args, int), &arg, count, 0);
	else if (arg.spec == 4)
		print_hex((unsigned int)va_arg(*args, int), &arg, count, 1);
	else if (arg.spec == 5)
		print_unsigned((unsigned int)va_arg(*args, int), &arg, count);
	else if (arg.spec == 6)
		print_pointer(va_arg(*args, void *), &arg, count);
	else if (arg.spec == 7)
		print_persent(&arg, count);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			count;
	const char	*str;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			str = format;
			if (!string_builder(&format, &args, &count))
			{
				ft_cputchar('%', &count);
				format = ++str;
			}
		}
		else
			format += ft_cputchar(*format, &count);
	}
	va_end(args);
	return (count);
}
