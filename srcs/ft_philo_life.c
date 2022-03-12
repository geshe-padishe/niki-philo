#include "ft_philo.h"

bool	ft_fork_and_eat(t_philo *philo, pthread_mutex_t *l_mtx,
		pthread_mutex_t	*r_mtx)
{
	if (ft_philo_death(philo) == 1)
		return (1);
	pthread_mutex_lock(l_mtx);
	ft_write("has taken a fork\n", philo, 0);
	if (ft_philo_death(philo) == 1)
	{
		pthread_mutex_unlock(l_mtx);
		return (1);
	}
	pthread_mutex_lock(r_mtx);
	if (ft_philo_death(philo) == 1)
	{
		pthread_mutex_unlock(l_mtx);
		pthread_mutex_unlock(r_mtx);
		return (1);
	}	
	ft_put_fork_eat(philo);
	ft_timeget(&philo->ate_time);
	ft_sleep(philo->table->time_to_eat, philo->dead, philo);
	pthread_mutex_unlock(l_mtx);
	pthread_mutex_unlock(r_mtx);
	return (0);
}

bool	ft_eat(t_philo *philo)
{
	t_philo			*philos;
	int				nb_cells;
	pthread_mutex_t	*l_mtx;
	pthread_mutex_t	*r_mtx;
	pthread_mutex_t	*swp;

	if (philo->dead || ft_philo_death(philo))
		return (1);
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
	return (ft_fork_and_eat(philo, l_mtx, r_mtx));
}

bool	ft_philo_death(t_philo *philo)
{
	struct timeval	time;

	ft_timeget(&time);
	pthread_mutex_lock(philo->wr_mutex);
	if (philo->table->dead)
	{
		pthread_mutex_unlock(philo->wr_mutex);	
		return (1);
	}
	if (philo->table->printed_death == 0 && 
		ft_timediff_us(time, philo->ate_time) >=
		philo->table->time_to_die * 1000)
	{
		philo->table->dead = 1;
		pthread_mutex_unlock(philo->wr_mutex);
		ft_put_death(philo);
		pthread_mutex_lock(philo->wr_mutex);
		philo->table->printed_death = 1;
		pthread_mutex_unlock(philo->wr_mutex);
		return (1);
	}
	else
		pthread_mutex_unlock(philo->wr_mutex);
	return (0);
}

int	ft_fork_index(int	index, int nb_cells)
{
	if (index == -1)
		return (nb_cells - 1);
	else if (index == nb_cells)
		return (0);
	return (index);
}