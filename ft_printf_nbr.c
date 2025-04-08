#include "ft_printf.h"
#include <stdio.h>

void	update_arg(t_arg *arg, char *str)
{
	if ((arg->flag[1] || arg->flag[2]) && *str != '-')
		arg->width--;
	if (arg->prec == 0 && *str == '0')
		*str = '\0';
	if (arg->prec > 0)
	{
		arg->prec = arg->prec - ft_strlen(str);
		if (*str == '-')
			arg->prec++;
		if (arg->prec > 0)
			arg->width -= arg->prec;
		else
			arg->prec = 0;
	}
}

void	print_int(int num, t_arg *arg, int *count)
{
	char	*str;

	str = ft_itoa(num);
	update_arg(arg, str);
	if (!arg->flag[0])
	{
		if (!arg->flag[3] || arg->prec >= 0)
			print_surplus(arg->width - ft_strlen(str), ' ', count);
	}
	print_flag(arg, str, count);
	if (arg->flag[3] && !arg->flag[0] && !arg->prec_bool)
		print_surplus(arg->width - ft_strlen(str), '0', count);
	if (arg->prec > 0)
	{
		print_flag(arg, str, count);
		print_surplus(arg->prec, '0', count);
	}
	ft_cputstr(str, count);
	if (arg->flag[0])
		print_surplus(arg->width - ft_strlen(str), ' ', count);
	free(str);
}

void	print_hex(unsigned int num, t_arg *arg, int *count, int cap)
{
	char	*str;

	str = ft_dtoh((unsigned long)num, cap);
	if (!str)
		return ;
	if (arg->flag[4] && num != 0)
		arg->width -= 2;
	update_arg(arg, str);
	if (!arg->flag[0] && (!arg->flag[3] || arg->prec_bool))
		print_surplus(arg->width - ft_strlen(str), ' ', count);
	if (arg->flag[4] && num != 0 && !cap)
		ft_cputstr("0x", count);
	if (arg->flag[4] && num != 0 && cap)
		ft_cputstr("0X", count);
	if (!arg->flag[0] && arg->flag[3] && !arg->prec_bool)
		print_surplus(arg->width - ft_strlen(str), '0', count);
	print_n_zeros(arg->prec, count);
	ft_cputstr(str, count);
	if (arg->flag[0])
		print_surplus(arg->width - ft_strlen(str), ' ', count);
	free(str);
}

void	print_pointer(void *ptr, t_arg *arg, int *count)
{
	char	*str;

	str = ft_dtoh((unsigned long)ptr, 0);
	arg->width -= 2;
	if (!arg->flag[0])
		print_surplus(arg->width - ft_strlen(str), ' ', count);
	ft_cputstr("0x", count);
	ft_cputstr(str, count);
	if (arg->flag[0])
		print_surplus(arg->width - ft_strlen(str), ' ', count);
	free(str);
}

void	print_unsigned(unsigned int num, t_arg *arg, int *count)
{
	char	*str;

	str = ft_utoa(num);
	update_arg(arg, str);
	if (arg->flag[3] && !arg->flag[0] && !arg->prec_bool)
	{
		print_surplus(arg->width - ft_strlen(str), '0', count);
		ft_cputstr(str, count);
	}
	else if (!arg->flag[0])
	{
		print_surplus(arg->width - ft_strlen(str), ' ', count);
		if (arg->prec > 0)
			print_surplus(arg->prec, '0', count);
		ft_cputstr(str, count);
	}
	else if (arg->flag[0])
	{
		if (arg->prec > 0)
			print_surplus(arg->prec, '0', count);
		ft_cputstr(str, count);
		print_surplus(arg->width - ft_strlen(str), ' ', count);
	}
	free(str);
}
