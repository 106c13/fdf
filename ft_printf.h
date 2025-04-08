#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct s_arg
{
	int	spec;
	int	flag[5];
	int	width;
	int	prec;
	int	prec_bool;
	int	lenght;
}	t_arg;

int		ft_printf(const char *format, ...);

int		ft_cputchar(char c, int *count);
void	ft_cputstr(const char *str, int *count);
char	*ft_dtoh(unsigned long num, int cap);
char	*ft_utoa(unsigned int num);

void	find_flag(const char **format, t_arg *arg);
void	find_width(const char **format, t_arg *arg);
void	find_specifier(const char **format, t_arg *arg);
void	find_precision(const char **format, t_arg *arg);

void	format_parser(const char **format, t_arg *arg);
int		string_builder(const char **format, va_list *args, int *count);

void	print_surplus(int size, char pad, int *count);
void	print_n_zeros(int n, int *count);
void	print_negative_num(char *str, int *count, int width);
void	print_flag(t_arg *arg, char *str, int *count);

void	print_int(int num, t_arg *arg, int *count);
void	print_char(char c, t_arg *arg, int *count);
void	print_hex(unsigned int num, t_arg *arg, int *count, int cap);
void	print_string(char *str, t_arg *arg, int *count);
void	print_pointer(void *ptr, t_arg *arg, int *count);
void	print_unsigned(unsigned int num, t_arg *arg, int *count);
void	print_persent(t_arg *arg, int *count);

size_t	ft_strlen(const char *str);
void	*ft_memset(void *ptr, int value, size_t num);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *s);
char	*ft_itoa(int n);
#endif
