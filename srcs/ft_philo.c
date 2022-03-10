#include "ft_philo.h"

void *routine(void *ptr)
{
	t_philo			*philo;
	struct timeval	time;

	philo = ptr;
	philo->dead = 0;
	if (philo->id % 2)
		ft_sleep(50, 0);
	while (philo->dead == 0)
	{
		pthread_mutex_lock(philo->rd_mutex);
		if (philo->table->dead == 1 || ft_timeget(&time))
		{
			pthread_mutex_unlock(philo->rd_mutex);
			return (NULL);
		}
		if (ft_timediff_us(time, philo->ate_time) >=
			philo->table->time_to_die * 1000)
		{
			pthread_mutex_unlock(philo->rd_mutex);
			pthread_mutex_lock(philo->wr_mutex);
			philo->table->dead = 1;
			pthread_mutex_unlock(philo->wr_mutex);
			ft_write("died\n", philo, 1);
			pthread_mutex_lock(philo->wr_mutex);
			philo->table->printed_death = 1;
			pthread_mutex_unlock(philo->wr_mutex);
			break;
		}
		pthread_mutex_unlock(philo->rd_mutex);
		philo->ate_time = time;
		ft_write("is eating\n", philo, 0);
		ft_sleep(philo->table->time_to_eat, philo->dead);
		ft_write("is sleeping\n", philo, 0);
		ft_sleep(philo->table->time_to_sleep, philo->dead);
		ft_write("is thinking\n", philo, 0);
	}
	return (philo);
}

char	*create_philos(t_table *table, pthread_mutex_t *wr_mutex,
		pthread_mutex_t *rd_mutex, pthread_mutex_t *sleep_mutex)
{
	unsigned long	i;
	t_philo			philo;
	bool			dead;

	ft_init_mutex(wr_mutex, rd_mutex, sleep_mutex);
	i = 0;
	while (i < table->nb_philos)
	{
		ft_mutex_philo(&philo, wr_mutex, rd_mutex, sleep_mutex);
		philo.table = table;
		philo.id = i;
		if (ft_timeget(&philo.ate_time) || ft_timeget(&philo.start_time))
			return (NULL);
		if (push_dynarray(table->darr, &philo, 1, 0) == -1)
			return (NULL);
		if (pthread_create(&((t_philo *)table->darr->list)[i].thread, NULL,
							&routine, &((t_philo *)table->darr->list)[i]))
			return (NULL);
		i++;
	}
	dead = 0;
	while (dead == 0)
	{
		pthread_mutex_lock(wr_mutex);
		dead = table->dead;
		pthread_mutex_unlock(wr_mutex);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_table			table;
	t_dynarray		darr;

	pthread_mutex_t	wr_mutex;
	pthread_mutex_t	rd_mutex;
	pthread_mutex_t	sleep_mutex;
	ft_memset(&table, sizeof(t_table));
	if (argc != 6 || parse_args(argv, &table) != 0)
		return (printf("Invalid Args\n"), -1);
	if (init_dynarray(&darr, table.nb_philos, sizeof(t_philo)) == -1)
		return (free_dynarray(&darr), -1);
	table.darr = &darr;
	create_philos(&table, &wr_mutex, &rd_mutex, &sleep_mutex);
	//printf("addr = %p\n", ((t_philo *)darr.list)[0].wr_mutex);
	if (ft_join_threads(&table))
		return (-1);
	ft_destroy_mutex(&wr_mutex, &rd_mutex, &sleep_mutex);
	return (dprintf(1, "MAIN RETURN\n"), free_dynarray(&darr), 0);
}
