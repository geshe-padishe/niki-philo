#include "ft_philo.h"

void	ft_memset(void *mem, size_t size)
{
	size_t	i;
	char	*ptr;

	if (!mem)
		return ;
	i = 0;
	ptr = (char *)mem;
	while (i < size)
	{
		ptr[i] = 0;
		i++;
	}
}
