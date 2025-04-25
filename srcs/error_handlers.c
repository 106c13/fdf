#include "fdf.h"

int	error(char *msg, int error_code)
{
	ft_printf(msg);
	return (error_code);
}

void	*error_ptr(char *msg, void *ptr)
{
	ft_printf(msg);
	return (ptr);
}
