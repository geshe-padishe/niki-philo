#include "ft_philo.h"

int	ft_sleep(long millisec)
{
	long	time;

	time = 0;
	while (time < millisec * 1000)
	{
		if (usleep(1000))
			return (-1);
		time += 1000;
	}
	return (0);
}

int	ft_ms(long *ms)
{
	struct timeval	time_val;

	if (gettimeofday(&time_val, NULL))
		return (-1);
	*ms = time_val.tv_sec * 1000 + time_val.tv_usec / 1000;
	return (0);
}

int	ft_timeget(struct timeval *time_val)
{
	if (gettimeofday(time_val, NULL))
		return (-1);
	return (0);
}

int	ft_timediff_ms(struct timeval time_val, struct timeval time_val2)
{
	int	ms;

	ms = (time_val.tv_sec - time_val2.tv_sec) * 1000 +
		(time_val.tv_usec - time_val2.tv_usec) / 1000;
	return (ms);
}
