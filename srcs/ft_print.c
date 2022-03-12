#include "ft_philo.h"

void	print_table(t_table table)
{
	printf("nb_philos = %ld\n", table.nb_philos);
	printf("time_to_die = %ld\n", table.time_to_die);
	printf("time_to_eat = %ld\n", table.time_to_eat);
	printf("time_to_sleep = %ld\n", table.time_to_sleep);
	printf("nb_meals = %ld\n", table.nb_meals);
}

int	ft_puttime(struct timeval start_time)
{
	struct timeval	current_time;

	if (ft_timeget(&current_time))
		return (-1);
	ft_putnbr(ft_timediff_us(current_time, start_time) / 1000);
	write(1, " ", 1);
	return (0);
}

void	ft_putnbr(int nbr)
{
	char	c;

	c = nbr % 10 + 48;
	if (nbr > 9)
		ft_putnbr(nbr / 10);
	write(1, &c, 1);
}

bool	ft_write(char *str, t_philo *philo, bool death)
{
	if (death)
		return (1);
	if (ft_philo_death(philo))
		return (1);
	pthread_mutex_lock(philo->wr_mutex);
	if(philo->table->dead)
	{
		pthread_mutex_unlock(philo->wr_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->wr_mutex);
	pthread_mutex_lock(philo->rd_mutex);
	ft_puttime(philo->start_time);
	write(1, "Philo ", 6);
	ft_putnbr(philo->id + 1);
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(philo->rd_mutex);
	return (0);
}
