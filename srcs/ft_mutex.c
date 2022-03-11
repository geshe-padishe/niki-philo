#include "ft_philo.h"

void	ft_mutex_philo(t_philo *philo, pthread_mutex_t *wr_mutex,
		pthread_mutex_t *rd_mutex, pthread_mutex_t *sleep_mutex)
{
	philo->dead = 0;
	philo->wr_mutex = wr_mutex;
	philo->rd_mutex = rd_mutex;
	philo->sleep_mutex = sleep_mutex;
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

void	ft_eat(t_philo *philo)
{
	t_philo			*philos;
	int				nb_cells;
	pthread_mutex_t	*l_mtx;
	pthread_mutex_t	*r_mtx;
	pthread_mutex_t	*swp;

	pthread_mutex_lock(philo->wr_mutex);
	philos = philo->table->darr->list;
	nb_cells = (int)philo->table->darr->nb_cells;
	l_mtx = &philos[ft_fork_index(philo->id, nb_cells)].fork;
	r_mtx = &philos[ft_fork_index(philo->id + 1, nb_cells)].fork;
	pthread_mutex_unlock(philo->wr_mutex);
	if (philo->id == nb_cells - 1)
	{
		swp = l_mtx;
		l_mtx = r_mtx;
		r_mtx = swp;
	}
	pthread_mutex_lock(l_mtx);
	ft_write("has taken a fork\n", philo, 0);
	pthread_mutex_lock(r_mtx);
	ft_write("has taken a fork\n", philo, 0);
	ft_write("is eating\n", philo, 0);
	ft_sleep(philo->table->time_to_eat, philo->dead);
	pthread_mutex_unlock(l_mtx);
	pthread_mutex_unlock(r_mtx);
}

int	ft_fork_index(int	index, int nb_cells)
{
	if (index == -1)
		return (nb_cells - 1);
	else if (index == nb_cells)
		return (0);
	return (index);
}
