#include "ft_philo.h"

int	ft_sleep(long millisec, bool dead, t_philo *philo)
{
	struct timeval	time;
	struct timeval	time2;

	if (dead == 0)
	{
		ft_timeget(&time);
		ft_timeget(&time2);
		while (ft_timediff_us(time2, time) < millisec * 1000)
		{
			if (philo && ft_philo_death(philo))
				return (1);
			if (usleep(1000))
				return (-1);
			ft_timeget(&time2);
		}
		return (0);
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

int	ft_timediff_us(struct timeval time_val, struct timeval time_val2)
{
	int	us;

	us = (time_val.tv_sec - time_val2.tv_sec) * 1000000 +
		(time_val.tv_usec - time_val2.tv_usec);
	return (us);
}
