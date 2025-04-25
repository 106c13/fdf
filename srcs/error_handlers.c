#include "fdf.h"

int	error(char *msg, int error_code)
{
	while (*msg)
		write(1, msg++, 1);
	return (error_code);
}

void	*error_ptr(char *msg, void *ptr)
{
	while (*msg)
		write(1, msg++, 1);
	return (ptr);
}
