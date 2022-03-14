#include "ft_philo.h"

void	print_table(t_table table)
{
	printf("nb_philos = %ld\n", table.nb_philos);
	printf("time_to_die = %ld\n", table.time_to_die);
	printf("time_to_eat = %ld\n", table.time_to_eat);
	printf("time_to_sleep = %ld\n", table.time_to_sleep);
	printf("nb_meals = %ld\n", table.nb_meals);
}

bool	ft_write(char *str, t_philo *philo, bool death)
{
	struct timeval	current_time;

	if (death)
		return (1);
	pthread_mutex_lock(philo->rd_mutex);
	if (ft_philo_death(philo))
	{
		pthread_mutex_unlock(philo->rd_mutex);
		return (1);
	}
	if (ft_timeget(&current_time))
		return (-1);
	printf("%i Philo %i %s", ft_timediff_us(current_time, philo->start_time) / 1000,
			philo->id + 1, str);
	pthread_mutex_unlock(philo->rd_mutex);
	return (0);
}

bool	ft_put_fork_eat(t_philo *philo)
{
	struct timeval	current_time;

	pthread_mutex_lock(philo->rd_mutex);
	if (ft_philo_death(philo))
	{
		pthread_mutex_unlock(philo->rd_mutex);
		return (1);
	}
	if (ft_timeget(&current_time))
		return (1);
	printf("%i Philo %i has taken a fork\n",
			ft_timediff_us(current_time, philo->start_time) / 1000,
			philo->id + 1);
	printf("%i Philo %i is eating\n",
			ft_timediff_us(current_time, philo->start_time) / 1000,
			philo->id + 1);
	pthread_mutex_lock(philo->meal_mutex);
	philo->meals += 1;
	pthread_mutex_unlock(philo->meal_mutex);
	pthread_mutex_unlock(philo->rd_mutex);
	return (0);
}

void	ft_put_death(t_philo *philo)
{
	struct timeval	current_time;

	if (ft_timeget(&current_time))
		return ;
	printf("%i Philo %i died\n",
			ft_timediff_us(current_time, philo->start_time) / 1000,
			philo->id + 1);
}
