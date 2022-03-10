#include "ft_philo.h"

int ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_join_threads(t_table *table)
{
	long unsigned i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_join(((t_philo *)table->darr->list)[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

void	ft_mutex_philo(t_philo *philo, pthread_mutex_t *wr_mutex,
		pthread_mutex_t *rd_mutex, pthread_mutex_t *sleep_mutex)
{
	philo->dead = 0;
	philo->wr_mutex = wr_mutex;
	philo->rd_mutex = rd_mutex;
	philo->sleep_mutex = sleep_mutex;
}

void	ft_init_mutex(pthread_mutex_t *wr_mutex,
		pthread_mutex_t *rd_mutex, pthread_mutex_t *sleep_mutex)
{
	pthread_mutex_init(wr_mutex, NULL);
	pthread_mutex_init(rd_mutex, NULL);
	pthread_mutex_init(sleep_mutex, NULL);
}

void	ft_destroy_mutex(pthread_mutex_t *wr_mutex,
		pthread_mutex_t *rd_mutex, pthread_mutex_t *sleep_mutex)
{
	pthread_mutex_destroy(wr_mutex);
	pthread_mutex_destroy(sleep_mutex);
	pthread_mutex_destroy(rd_mutex);
}
