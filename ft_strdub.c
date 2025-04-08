#include "ft_printf.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	size;
	size_t	i;

	size = ft_strlen(s);
	str = malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	i = 0;
	while (i < size)
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}
