#include "ft_philo.h"

int	ft_sleep(unsigned long microsec)
{
	unsigned long	time;

	time = 0;
	while (time < microsec)
	{
		if (usleep(1000))
			return (-1);
		time += 1000;
	}
	return (0);
}
