#include "ft_philo.h"

int	ft_sleep(long millisec)
{
	struct timeval	time;
	struct timeval	time2;

	ft_timeget(&time);
	while (ft_timediff_us(time2, time) < millisec * 1000)
	{
		if (usleep(10))
			return (-1);
		ft_timeget(&time2);
	}
	return (0);
}

//int	ft_sleep(long time_to_do)
//{
//	long	time;
//	long	time2;
//
//	ft_ms(&time2);
//	usleep(((time_to_do * 1000) / 5) * 4);
//	ft_ms(&time);
//	while (time_to_do > time - time2)
//	{
//		usleep(1000);
//		ft_ms(&time);
//	}
//	return (0);
//}

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

int	ft_timediff_us(struct timeval time_val, struct timeval time_val2)
{
	int	us;

	us = (time_val.tv_sec - time_val2.tv_sec) * 1000000 +
		(time_val.tv_usec - time_val2.tv_usec);
	return (us);
}
