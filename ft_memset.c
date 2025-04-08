#include "ft_printf.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*byte_ptr;
	unsigned char	byte_value;
	size_t			i;

	byte_ptr = (unsigned char *)ptr;
	byte_value = (unsigned char)value;
	i = 0;
	while (i < num)
	{
		byte_ptr[i] = byte_value;
		i++;
	}
	return (ptr);
}
