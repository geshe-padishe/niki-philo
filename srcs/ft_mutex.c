#include "ft_philo.h"

void	ft_mutex_philo(t_philo *philo, pthread_mutex_t *wr_mutex,
		pthread_mutex_t *rd_mutex, pthread_mutex_t *sleep_mutex)
{
	philo->dead = 0;
	philo->wr_mutex = wr_mutex;
	philo->rd_mutex = rd_mutex;
	philo->meal_mutex = sleep_mutex;
}

void	ft_init_mutex(pthread_mutex_t *wr_mutex, pthread_mutex_t *rd_mutex,
					pthread_mutex_t *sleep_mutex, pthread_mutex_t *forks_mutex)
{
	pthread_mutex_init(wr_mutex, NULL);
	pthread_mutex_init(rd_mutex, NULL);
	pthread_mutex_init(sleep_mutex, NULL);
	pthread_mutex_init(forks_mutex, NULL);
}

void	ft_destroy_mutex(pthread_mutex_t *wr_mutex, pthread_mutex_t *rd_mutex,
						pthread_mutex_t *sleep_mutex,
						pthread_mutex_t *forks_mutex)
{
	pthread_mutex_destroy(wr_mutex);
	pthread_mutex_destroy(sleep_mutex);
	pthread_mutex_destroy(rd_mutex);
	pthread_mutex_destroy(forks_mutex);
}
